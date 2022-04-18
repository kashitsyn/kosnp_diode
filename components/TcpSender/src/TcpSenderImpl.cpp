#include "TcpSenderImpl.hpp"

#include <unistd.h>

#include <cstring>

#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/select.h>

#include <iostream>

#include <ExceptionHelper.hpp>

using namespace std::chrono_literals;
using namespace std::string_literals;

namespace diode
{

TcpSenderImpl::TcpSenderImpl(std::shared_ptr<const DataStorage> dataStorage)
    : BaseService("TCP Sender"s)
    , m_dataStorage(std::move(dataStorage))
{}

void TcpSenderImpl::Consume(const DataItem& item)
{
    const auto lock = std::lock_guard(m_queueMutex);
    m_queue.push(item);
}

void TcpSenderImpl::DoUp()
{
    const auto settings = *m_dataStorage->Get("SenderSettings"s);

    // NOTE: We need to clear output streams, because they may be in a wrong
    // state due to conflicts with KSS restrictions in previous state.
    std::cout.clear();
    std::cerr.clear();

    std::cout << "Info: " << GetName() << " settings: " << settings << std::endl;

    const auto pos = settings.find(':');
    m_address = settings.substr(0, pos);
    m_port = std::stoul(settings.substr(pos + 1, settings.length()));

    m_task.Start();
}

void TcpSenderImpl::Run(StopToken stopToken)
{
    try
    {
        InitServer();
        while (!stopToken.IsStopRequested())
        {
            DoProcess(stopToken);
        }
        DeinitServer();
    }
    catch (const std::exception& e)
    {
        const auto errorMsg = ExceptionHelper::CreateErrorMessage();
        std::cerr << "Error: " << GetName() << " failed to run: " << errorMsg << std::endl;

        DeinitServer();

        throw;
    }
}

void TcpSenderImpl::DoProcess(StopToken stopToken)
{
    fd_set readSet;
    fd_set writeSet;

    while (!stopToken.IsStopRequested())
    {
        FD_ZERO(&readSet);
        FD_ZERO(&writeSet);

        FD_SET(m_serverSocket, &readSet);
        if (m_clientSocket != -1)
        {
            FD_SET(m_clientSocket, &writeSet);
        }

        timeval tv{};
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        auto rc = select(std::max(m_serverSocket, m_clientSocket) + 1, &readSet, &writeSet, nullptr, &tv);
        if (rc == -1)
        {
            std::cerr << "Error: " << GetName() << " failed to select: " << strerror(errno) << std::endl;
            throw TcpSenderException();
        }

        if (FD_ISSET(m_serverSocket, &readSet))
        {
            HandleIncomingConnection();
        }

        if (m_clientSocket != -1 && FD_ISSET(m_clientSocket, &writeSet))
        {
            const auto message = TakeMessageToSend();
            if (message)
            {
                SendMessage(*message);
            }
        }

        stopToken.WaitFor(100ms); // NOTE: In order to decrease CPU load.
    }
}

void TcpSenderImpl::InitServer()
{
    sockaddr_in stSockAddr{};

    const auto serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == -1)
    {
        std::cerr << "Error: " << GetName() << " can't create socket: " << strerror(errno) << std::endl;
        throw TcpSenderException();
    }

    memset(&stSockAddr, 0, sizeof(stSockAddr));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(m_port);
    stSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serverSocket, (sockaddr*)&stSockAddr, sizeof(stSockAddr)) == -1)
    {
        std::cerr << "Error: " << GetName() << " failed to bind: " << strerror(errno) << std::endl;
        close(serverSocket);
        throw TcpSenderException();
    }

    if (listen(serverSocket, 1) == -1)
    {
        std::cerr << "Error: " << GetName() << " failed to listen: " << strerror(errno) << std::endl;
        close(serverSocket);
        throw TcpSenderException();
    }

    m_serverSocket = serverSocket;
}

void TcpSenderImpl::DeinitServer()
{
    if (m_clientSocket != -1)
    {
        close(m_clientSocket);
        m_clientSocket = -1;
    }

    if (m_serverSocket != -1)
    {
        close(m_serverSocket);
        m_serverSocket = -1;
    }
}

void TcpSenderImpl::HandleIncomingConnection()
{
    auto socket = accept(m_serverSocket, nullptr, nullptr);
    if (socket == -1)
    {
        std::cerr << "Error: " << GetName() << " failed to accept: " << strerror(errno) << std::endl;
        close(m_serverSocket);
        throw TcpSenderException();
    }

    if (m_clientSocket == -1)
    {
        std::cout << "Info: Client connected to " << GetName() << std::endl;
        m_clientSocket = socket;
    }
    else
    {
        std::cerr << "Warning: " << GetName() << " supports only 1 connection at the moment" << std::endl;
        close(socket);
    }
}

void TcpSenderImpl::SendMessage(const std::string& message) const
{
    if (send(m_clientSocket,  message.c_str(), message.length() + 1, 0) == -1)
    {
        std::cerr << "Error: " << GetName() << " failed to send: " << strerror(errno) << std::endl;
        close(m_clientSocket);
        throw TcpSenderException();
    }
    else
    {
        std::cout << "Info: " << GetName() << " sent: " << message << std::flush;
    }
}

std::optional<std::string> TcpSenderImpl::TakeMessageToSend()
{
    const auto lock = std::lock_guard(m_queueMutex);
    if (m_queue.empty())
    {
        return std::nullopt;
    }

    const auto message = m_queue.front().value;
    m_queue.pop();
    return message;
}

void TcpSenderImpl::DoDown()
{
    m_task.Stop();

    m_port = -1;
    m_address = {};
}


TcpSenderImplFactory::TcpSenderImplFactory() = default;

std::unique_ptr<TcpSender>
TcpSenderImplFactory::operator()(
    std::shared_ptr<const DataStorage> dataStorage
)
{
    return std::make_unique<TcpSenderImpl>(std::move(dataStorage));
}

} // namespace diode

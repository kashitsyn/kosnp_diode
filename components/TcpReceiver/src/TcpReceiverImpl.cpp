#include "TcpReceiverImpl.hpp"

#include <unistd.h>

#include <cassert>
#include <cstring>

#include <netdb.h>
#include <netinet/in.h>

#include <sys/socket.h>

#include <iostream>

#include <ExceptionHelper.hpp>

#define RECEIVE_BUF_SIZE 1024

using namespace std::chrono_literals;
using namespace std::string_literals;

namespace diode
{

TcpReceiverImpl::TcpReceiverImpl(
    std::shared_ptr<const DataStorage> dataStorage,
    std::shared_ptr<Consumer> consumer
)
    : BaseService("TCP Receiver"s)
    , m_dataStorage(std::move(dataStorage))
    , m_consumer(std::move(consumer))
{}

void TcpReceiverImpl::DoUp()
{
    const auto settings = *m_dataStorage->Get("ReceiverSettings"s);

    std::cout << "Info: " << GetName() << " settings: " << settings << std::endl;

    const auto pos = settings.find(':');
    m_address = settings.substr(0, pos);
    m_port = std::stoul(settings.substr(pos + 1, settings.length()));

    m_task.Start();
}

void TcpReceiverImpl::Run(StopToken stopToken)
{
    try
    {
        while (!stopToken.IsStopRequested())
        {
            DoProcess(stopToken);
            stopToken.WaitFor(5s);
        }
    }
    catch (...)
    {
        const auto errorMsg = ExceptionHelper::CreateErrorMessage();
        std::cerr << "Error: " << GetName() << " failed to run: " << errorMsg << std::endl;
        throw;
    }
}

void TcpReceiverImpl::DoProcess(StopToken stopToken)
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == -1)
    {
        std::cerr << "Error: " << GetName() << " can't create socket: " << strerror(errno) << std::endl;
        throw TcpReceiverException();
    }

    sockaddr_in stSockAddr{};
    memset(&stSockAddr, 0, sizeof(stSockAddr));
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(m_port);

    addrinfo hints{};
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo *resultHints = nullptr;
    auto res = getaddrinfo(m_address.c_str(), nullptr, &hints, &resultHints);
    if (res != 0)
    {
        std::cerr << "Error: " << GetName() << " can't get address info: " << strerror(errno) << std::endl;
        close(clientSocket);
        throw TcpReceiverException();
    }

    auto in_addr = (sockaddr_in*)resultHints->ai_addr;
    memcpy(&stSockAddr.sin_addr.s_addr, &in_addr->sin_addr.s_addr, sizeof(in_addr_t));
    freeaddrinfo(resultHints);

    res = connect(clientSocket, (sockaddr*)&stSockAddr, sizeof(stSockAddr));
    if (res == -1)
    {
        std::cerr << "Warning: "
            << GetName() << " failed to connect: " << strerror(errno) << ". "
            << GetName() << " will try to connect after a timeout" << std::endl;
        close(clientSocket);
        return;
    }

    std::cout << "Info: " << GetName() << " connected to Server" << std::endl;

    while (!stopToken.IsStopRequested())
    {
        char buf[RECEIVE_BUF_SIZE];
        const auto rc = recv(clientSocket, buf, sizeof(buf) - 1, 0);
        if (rc > 0)
        {
            buf[rc] = '\0';
            std::cout << "Info: " << GetName() << " received: " << buf << std::flush;
            m_consumer->Consume({buf});
        }
        else
        {
            shutdown(clientSocket, SHUT_RDWR);
            close(clientSocket);

            if (rc == 0)
            {
                std::cout << "Info: " << GetName() << " lost connection to Server" << std::endl;
                return;
            }
            else
            {
                assert(rc == -1);
                std::cerr << "Error: " << GetName() << " failed to receive: " << strerror(errno) << std::endl;
                throw TcpReceiverException();
            }
        }
    }
}

void TcpReceiverImpl::DoDown()
{
    m_task.Stop();

    m_port = -1;
    m_address = {};
}

TcpReceiverImplFactory::TcpReceiverImplFactory() = default;

std::unique_ptr<TcpReceiver>
TcpReceiverImplFactory::operator()(
    std::shared_ptr<const DataStorage> dataStorage,
    std::shared_ptr<Consumer> consumer
)
{
    return std::make_unique<TcpReceiverImpl>(std::move(dataStorage), std::move(consumer));
}

} // namespace diode

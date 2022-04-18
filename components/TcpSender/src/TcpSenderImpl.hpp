#ifndef DIODE_TCP_SENDER_IMPL_HPP
#define DIODE_TCP_SENDER_IMPL_HPP

#include <mutex>
#include <queue>

#include <BaseService.hpp>

#include <Task.hpp>

#include <TcpSenderException.hpp>
#include <TcpSenderImplFactory.hpp>

namespace diode
{

class TcpSenderImpl
    : public TcpSender
    , public BaseService
{

public:

    explicit
    TcpSenderImpl(std::shared_ptr<const DataStorage> dataStorage);

    void Consume(const DataItem& item) override;

protected:

    void DoUp() override;

    void DoDown() override;

private:

    void Run(StopToken stopToken);

    void DoProcess(StopToken stopToken);

    void InitServer();

    void DeinitServer();

    void HandleIncomingConnection();

    void SendMessage(const std::string& message) const;

    std::optional<std::string> TakeMessageToSend();

private:

    int m_serverSocket = -1;
    int m_clientSocket = -1;

    std::shared_ptr<const DataStorage> m_dataStorage;
    
    std::queue<DataItem> m_queue;
    std::mutex m_queueMutex;

    std::string m_address{};
    uint16_t m_port{};

    Task m_task{&TcpSenderImpl::Run, this};

};

} // namespace diode

#endif // DIODE_TCP_SENDER_IMPL_HPP

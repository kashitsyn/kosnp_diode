#ifndef DIODE_TCP_RECEIVER_IMPL_HPP
#define DIODE_TCP_RECEIVER_IMPL_HPP

#include <BaseService.hpp>

#include <Task.hpp>

#include <TcpReceiverException.hpp>
#include <TcpReceiverImplFactory.hpp>
#include <Consumer.hpp>

namespace diode
{

class TcpReceiverImpl
    : public TcpReceiver
    , public BaseService
{

public:

    TcpReceiverImpl(
        std::shared_ptr<const DataStorage> dataStorage,
        std::shared_ptr<Consumer> consumer
    );

protected:

    void DoUp() override;

    void DoDown() override;

private:
    void Run(StopToken stopToken);

    void DoProcess(StopToken stopToken);

private:
    std::shared_ptr<const DataStorage> m_dataStorage;
    std::shared_ptr<Consumer> m_consumer;
    
    std::string m_address{};
    uint16_t m_port{};

    Task m_task{&TcpReceiverImpl::Run, this};

};

} // namespace diode

#endif // DIODE_TCP_RECEIVER_IMPL_HPP

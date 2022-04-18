#include "DiodeCoordinator.hpp"

#include <ConfigurationManagerImplFactory.hpp>
#include <InterrupterImplFactory.hpp>

#include <ServiceManagerImplFactory.hpp>
#include <TcpSenderImplFactory.hpp>
#include <TcpReceiverImplFactory.hpp>

namespace diode::app
{

//
// Implementation class
//

class DiodeCoordinator::Impl
{

public:

    // Coordinator

    void OnStartup()
    {
        m_serviceManager->Start();
    }

    void Wait() const
    {
        m_interrupter->Wait();
    }

    void OnShutdown()
    {
        m_serviceManager->Stop();
    }

private:

    std::unique_ptr<Interrupter> m_interrupter = InterrupterImplFactory{}();

    std::shared_ptr<ConfigurationManager> m_configurationManager = ConfigurationManagerImplFactory{}();

    std::shared_ptr<TcpSender> m_tcpSender =
        TcpSenderImplFactory{}(
            m_configurationManager
        );

    std::shared_ptr<TcpReceiver> m_tcpReceiver =
        TcpReceiverImplFactory{}(
            m_configurationManager,
            m_tcpSender
        );

    std::unique_ptr<ServiceManager> m_serviceManager =
        ServiceManagerImplFactory{}(
            m_tcpSender,
            m_tcpReceiver
        );

};

//
// Interface class
//

DiodeCoordinator::DiodeCoordinator()
    : m_impl{std::make_unique<Impl>()}
{}

DiodeCoordinator::~DiodeCoordinator() = default;

void DiodeCoordinator::OnStartup()
{
    m_impl->OnStartup();
}

void DiodeCoordinator::Wait() const
{
    m_impl->Wait();
}

void DiodeCoordinator::OnShutdown()
{
    m_impl->OnShutdown();
}

} // namespace diode::app

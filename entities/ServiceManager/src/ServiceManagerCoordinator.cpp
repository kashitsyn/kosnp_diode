#include "ServiceManagerCoordinator.hpp"

#include <iostream>

#include <CathodeDescription.h>
#include <AnodeDescription.h>

#include <StopToken.hpp>

#include <ServiceManagerImplFactory.hpp>
#include <AnodeClientImplFactory.hpp>
#include <CathodeClientImplFactory.hpp>

namespace diode
{

//
// Implementation class
//

class ServiceManagerCoordinator::Impl
{

public:

    // Coordinator

    void OnStartup()
    {
        m_serviceManager->Start();
    }

    void Wait() const
    {
        NonStopToken{}.Wait();
    }

    void OnShutdown()
    {
        m_serviceManager->Stop();
    }

private:

    std::unique_ptr<CathodeClient>
    m_tcpSenderClient =
        CathodeClientImplFactory{}(
            DIODE_CATHODE_SERVICE_NAME
        );

    std::unique_ptr<AnodeClient>
    m_anodeClient =
        AnodeClientImplFactory{}(
            DIODE_ANODE_SERVICE_NAME
        );

    std::unique_ptr<ServiceManager> m_serviceManager =
        ServiceManagerImplFactory{}(
            m_tcpSenderClient->GetTcpSender(),
            m_anodeClient->GetTcpReceiver()
        );

};

//
// Interface class
//

ServiceManagerCoordinator::ServiceManagerCoordinator()
    : m_impl{std::make_unique<Impl>()}
{}

ServiceManagerCoordinator::~ServiceManagerCoordinator() = default;

void ServiceManagerCoordinator::OnStartup()
{
    m_impl->OnStartup();
}

void ServiceManagerCoordinator::Wait() const
{
    m_impl->Wait();
}

void ServiceManagerCoordinator::OnShutdown()
{
    m_impl->OnShutdown();
}

} // namespace diode

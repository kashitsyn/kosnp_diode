#include "CathodeCoordinator.hpp"

#include <AnodeDescription.h>
#include <CathodeDescription.h>

#include <ConfigurationManagerImplFactory.hpp>
#include <StopToken.hpp>

#include <AnodeClientImplFactory.hpp>
#include <TcpSenderImplFactory.hpp>
#include <CathodeServerImplFactory.hpp>

using namespace std::string_literals;

namespace diode
{

//
// Implementation class
//

class CathodeCoordinator::Impl
{

public:

    // Coordinator

    void OnStartup()
    {
        m_tcpSenderServer->Start();
    }

    void Wait() const
    {
        NonStopToken{}.Wait();
    }

    void OnShutdown()
    {
        m_tcpSenderServer->Stop();
    }

private:

    std::unique_ptr<AnodeClient> m_anodeClient =
        AnodeClientImplFactory{}(
            DIODE_ANODE_SERVICE_NAME
        );

    std::shared_ptr<TcpSender> m_tcpSender =
        TcpSenderImplFactory{}(
            m_anodeClient->GetConfigurationManager()
        );

    std::unique_ptr<CathodeServer> m_tcpSenderServer =
        CathodeServerImplFactory{}(
            "TCP Sender"s
            , DIODE_CATHODE_SERVICE_NAME
            , m_tcpSender
        );

};

//
// Interface class
//

CathodeCoordinator::CathodeCoordinator()
    : m_impl{std::make_unique<Impl>()}
{}

CathodeCoordinator::~CathodeCoordinator() = default;

void CathodeCoordinator::OnStartup()
{
    m_impl->OnStartup();
}

void CathodeCoordinator::Wait() const
{
    m_impl->Wait();
}

void CathodeCoordinator::OnShutdown()
{
    m_impl->OnShutdown();
}

} // namespace diode

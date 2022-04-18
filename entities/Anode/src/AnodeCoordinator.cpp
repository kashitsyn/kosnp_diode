#include "AnodeCoordinator.hpp"

#include <CathodeDescription.h>

#include <AnodeDescription.h>

#include <ConfigurationManagerImplFactory.hpp>
#include <StopToken.hpp>

#include <TcpReceiverImplFactory.hpp>
#include <AnodeServerImplFactory.hpp>
#include <CathodeClientImplFactory.hpp>

using namespace std::string_literals;

namespace diode
{

//
// Implementation class
//

class AnodeCoordinator::Impl
{

public:

    // Coordinator

    void OnStartup()
    {
        m_anodeServer->Start();
    }

    void Wait() const
    {
        NonStopToken{}.Wait();
    }

    void OnShutdown()
    {
        m_anodeServer->Stop();
    }

private:

    std::unique_ptr<CathodeClient>
    m_tcpSenderClient =
        CathodeClientImplFactory{}(
            DIODE_CATHODE_SERVICE_NAME
        );

    std::shared_ptr<ConfigurationManager> m_configurationManager =
        ConfigurationManagerImplFactory{}();

    std::shared_ptr<TcpReceiver> m_tcpReceiver =
        TcpReceiverImplFactory{}(
            m_configurationManager,
            m_tcpSenderClient->GetTcpSender()
        );

    std::unique_ptr<AnodeServer>
    m_anodeServer =
        AnodeServerImplFactory{}(
            "TCP Receiver"s
            , DIODE_ANODE_SERVICE_NAME
            , m_tcpReceiver
            , m_configurationManager
        );

};

//
// Interface class
//

AnodeCoordinator::AnodeCoordinator()
    : m_impl{std::make_unique<Impl>()}
{}

AnodeCoordinator::~AnodeCoordinator() = default;

void AnodeCoordinator::OnStartup()
{
    m_impl->OnStartup();
}

void AnodeCoordinator::Wait() const
{
    m_impl->Wait();
}

void AnodeCoordinator::OnShutdown()
{
    m_impl->OnShutdown();
}

} // namespace diode

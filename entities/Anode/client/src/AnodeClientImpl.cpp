#include "AnodeClientImpl.hpp"

#include <cassert>

#include <string>

#include <coresrv/sl/sl_api.h>

namespace diode
{

AnodeClientImpl::AnodeClientImpl(std::string_view serviceName)
{
    m_handle = ServiceLocatorConnect(std::string{serviceName}.c_str());
    assert(m_handle != INVALID_HANDLE);

    nk_iid_t TcpReceiver_service_riid =
        ServiceLocatorGetRiid(
            m_handle,
            "tcpReceiver.service"
        );
    assert(TcpReceiver_service_riid != INVALID_RIID);

    m_tcpReceiverProxy =
        std::make_shared<TcpReceiverProxy>(
            std::make_unique<NkKosTransport>(m_handle)
            , TcpReceiver_service_riid
        );

    nk_iid_t ConfigurationManager_service_riid =
        ServiceLocatorGetRiid(
            m_handle,
            "configurationManager.dataStorage"
        );
    assert(ConfigurationManager_service_riid != INVALID_RIID);

    m_configurationManagerProxy =
        std::make_unique<ConfigurationManagerProxy>(
            std::make_unique<NkKosTransport>(m_handle)
            , ConfigurationManager_service_riid
        );
}

std::unique_ptr<AnodeClient>
AnodeClientImplFactory::operator()(std::string_view serviceName)
{
    return std::make_unique<AnodeClientImpl>(serviceName);
}

} // namespace diode

#include "CathodeClientImpl.hpp"

#include <cassert>

#include <string>

#include <coresrv/sl/sl_api.h>

namespace diode
{

CathodeClientImpl::CathodeClientImpl(std::string_view serviceName)
{
    m_handle = ServiceLocatorConnect(std::string{serviceName}.c_str());
    assert(m_handle != INVALID_HANDLE);

    nk_iid_t TcpSender_service_riid =
        ServiceLocatorGetRiid(
            m_handle,
            "tcpSender.service"
        );
    assert(TcpSender_service_riid != INVALID_RIID);

    nk_iid_t TcpSender_consumer_riid =
        ServiceLocatorGetRiid(
            m_handle,
            "tcpSender.consumer"
        );
    assert(TcpSender_consumer_riid != INVALID_RIID);

    m_TcpSenderProxy =
        std::make_shared<TcpSenderProxy>(
            std::make_unique<NkKosTransport>(m_handle)
            , TcpSender_service_riid
            , TcpSender_consumer_riid
        );
}

std::unique_ptr<CathodeClient>
CathodeClientImplFactory::operator()(std::string_view serviceName)
{
    return std::make_unique<CathodeClientImpl>(serviceName);
}

} // namespace diode

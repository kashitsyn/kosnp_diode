#include "CathodeServerImpl.hpp"

#include <cassert>

#include <utility>

extern "C"
{
#include <coresrv/nk/transport-kos-dispatch.h>
}
#include <coresrv/sl/sl_api.h>

namespace diode
{

CathodeServerImpl::CathodeServerImpl(
    std::string name
    , std::string_view serviceName
    , std::shared_ptr<TcpSender> TcpSenderImpl
)
    : BaseService(std::move(name))
    , m_TcpSenderSkeleton(std::move(TcpSenderImpl))
{
    ::diode_Cathode_entity_init(
        &m_entity,
        m_TcpSenderSkeleton.GetComponent()
    );

    ServiceId id; // unused
    m_handle = ServiceLocatorRegister(
        std::string{serviceName}.c_str(), nullptr, 0, &id);
    assert(m_handle != INVALID_HANDLE);
}

void CathodeServerImpl::DoUp()
{
    m_task.Start();
}

void CathodeServerImpl::DoDown()
{
    m_task.Stop();
}

Service::Status
CathodeServerImpl::GetOperatingStatus() const
{
    return m_task.IsFailed() ? Status::FailedToOperate : Status::OK;
}

void CathodeServerImpl::Run([[maybe_unused]] StopToken stopToken)
{
    NkKosDispatchInfo info = NK_ENTITY_DISPATCH_INFO_INITIALIZER(
        diode_Cathode,
        m_entity
    );
    NkKosDoDispatch(m_handle, &info);
}

std::unique_ptr<CathodeServer>
CathodeServerImplFactory::operator()(
    std::string name
    , std::string_view serviceName
    , std::shared_ptr<TcpSender> TcpSenderImpl
)
{
    return std::make_unique<CathodeServerImpl>(
        std::move(name)
        , serviceName
        , std::move(TcpSenderImpl)
    );
}

} // namespace diode

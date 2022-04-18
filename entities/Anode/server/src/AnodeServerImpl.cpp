#include "AnodeServerImpl.hpp"

#include <cassert>

#include <utility>

extern "C"
{
#include <coresrv/nk/transport-kos-dispatch.h>
}
#include <coresrv/sl/sl_api.h>

namespace diode
{

AnodeServerImpl::AnodeServerImpl(
    std::string name
    , std::string_view serviceName
    , std::shared_ptr<TcpReceiver> TcpReceiverImpl
    , std::shared_ptr<ConfigurationManager> configurationManagerImpl
)
    : BaseService(std::move(name))
    , m_TcpReceiverSkeleton(std::move(TcpReceiverImpl))
    , m_configurationManagerSkeleton(std::move(configurationManagerImpl))
{
    ::diode_Anode_entity_init(
        &m_entity,
        m_TcpReceiverSkeleton.GetComponent(),
        m_configurationManagerSkeleton.GetComponent()
    );

    ServiceId id; // unused
    m_handle = ServiceLocatorRegister(
        std::string{serviceName}.c_str(), nullptr, 0, &id);
    assert(m_handle != INVALID_HANDLE);
}

void AnodeServerImpl::DoUp()
{
    m_task.Start();
}

void AnodeServerImpl::DoDown()
{
    m_task.Stop();
}

Service::Status
AnodeServerImpl::GetOperatingStatus() const
{
    return m_task.IsFailed() ? Status::FailedToOperate : Status::OK;
}

void AnodeServerImpl::Run([[maybe_unused]] StopToken stopToken)
{
    NkKosDispatchInfo info = NK_ENTITY_DISPATCH_INFO_INITIALIZER(
        diode_Anode,
        m_entity
    );
    NkKosDoDispatch(m_handle, &info);
}

std::unique_ptr<AnodeServer>
AnodeServerImplFactory::operator()(
    std::string name
    , std::string_view serviceName
    , std::shared_ptr<TcpReceiver> TcpReceiverImpl
    , std::shared_ptr<ConfigurationManager> configurationManagerImpl
)
{
    return std::make_unique<AnodeServerImpl>(
        std::move(name)
        , serviceName
        , std::move(TcpReceiverImpl)
        , std::move(configurationManagerImpl)
    );
}

} // namespace diode

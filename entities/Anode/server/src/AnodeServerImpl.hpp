#ifndef DIODE_ANODE_SERVER_IMPL_HPP
#define DIODE_ANODE_SERVER_IMPL_HPP

#include <handle/handletype.h>

#include <BaseService.hpp>
#include <Task.hpp>

#include <diode/Anode.edl.h>

#include <ConfigurationManagerSkeleton.hpp>
#include <AnodeServerImplFactory.hpp>
#include <TcpReceiverSkeleton.hpp>

namespace diode
{

class AnodeServerImpl
    : public AnodeServer
    , private BaseService
{

public:

    explicit
    AnodeServerImpl(
        std::string name
        , std::string_view serviceName
        , std::shared_ptr<TcpReceiver> TcpReceiverImpl
        , std::shared_ptr<ConfigurationManager> configurationManagerImpl
    );

protected:

    // BaseService

    void DoUp() override;

    void DoDown() override;

    Status GetOperatingStatus() const override;

private:

    void Run(StopToken stopToken);

    TcpReceiverSkeleton m_TcpReceiverSkeleton;
    ConfigurationManagerSkeleton m_configurationManagerSkeleton;

    ::diode_Anode_entity m_entity{};
    Handle m_handle = INVALID_HANDLE;

    Task m_task{&AnodeServerImpl::Run, this};

};

} // namespace diode

#endif // DIODE_ANODE_SERVER_IMPL_HPP

#ifndef DIODE_CATHODE_SERVER_IMPL_HPP
#define DIODE_CATHODE_SERVER_IMPL_HPP

#include <handle/handletype.h>

#include <BaseService.hpp>
#include <Task.hpp>

#include <diode/Cathode.edl.h>

#include <CathodeServerImplFactory.hpp>
#include <TcpSenderSkeleton.hpp>

namespace diode
{

class CathodeServerImpl
    : public CathodeServer
    , private BaseService
{

public:

    explicit
    CathodeServerImpl(
        std::string name
        , std::string_view serviceName
        , std::shared_ptr<TcpSender> TcpSenderImpl
    );

protected:

    // BaseService

    void DoUp() override;

    void DoDown() override;

    Status GetOperatingStatus() const override;

private:

    void Run(StopToken stopToken);

    TcpSenderSkeleton m_TcpSenderSkeleton;

    ::diode_Cathode_entity m_entity{};
    Handle m_handle = INVALID_HANDLE;

    Task m_task{&CathodeServerImpl::Run, this};

};

} // namespace diode

#endif // DIODE_CATHODE_SERVER_IMPL_HPP

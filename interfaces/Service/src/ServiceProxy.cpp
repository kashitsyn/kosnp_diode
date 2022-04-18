#include <ServiceProxy.hpp>

#include <cassert>

#include <stdexcept>

#include <coresrv/nk/transport-kos.h>

#include <BaseException.hpp>
#include <ExceptionHelper.hpp>

using namespace std::string_view_literals;

namespace diode
{

ServiceProxy::ServiceProxy(nk_transport* transport, const nk_iid_t riid)
    : m_reqArena{std::make_unique<ReqArenaBuffer>()}
    , m_resArena{std::make_unique<ResArenaBuffer>()}
{
    ::diode_Service_proxy_init(&m_proxy, transport, riid);
}

std::string ServiceProxy::GetName() const
{
    ::diode_Service_GetName_req req{};
    nk_req_reset(&req);

    ::diode_Service_GetName_res res{};
    auto& resBuf = *m_resArena;
    nk_arena resArena = NK_ARENA_INITIALIZER(
        resBuf.data(), resBuf.data() + resBuf.size()
    );

    const auto rc = ::diode_Service_GetName(
        &m_proxy.base, &req, nullptr, &res, &resArena
    );
    HandleReturnCode(rc, res.rc, "ServiceProxy::GetName()"sv);

    auto name = std::string{};

    {
        nk_size_t resNameLength = 0;
        nk_char_t* resName = nk_arena_get(
            nk_char_t, &resArena,
            &res.name, &resNameLength
        );
        assert(resName != nullptr || resNameLength == 0);
        assert(resNameLength > 0);
        assert(resNameLength <= diode_Service_MaxServiceNameLength);

        name.assign(resName, resNameLength - 1);
    }

    return name;
}

void ServiceProxy::SetName(std::string name)
{
    ::diode_Service_SetName_req req{};
    nk_req_reset(&req);
    auto& reqBuf = *m_reqArena;
    nk_arena reqArena = NK_ARENA_INITIALIZER(
        reqBuf.data(), reqBuf.data() + reqBuf.size()
    );

    {
        auto rc = 0;

        assert(name.length() <= diode_Service_MaxServiceNameLength);
        rc = NkKosCopyStringToArena(&reqArena, &req.name, name.c_str());
        assert(rc == 0);
    }


    ::diode_Service_SetName_res res{};

    const auto rc = ::diode_Service_SetName(
        &m_proxy.base, &req, &reqArena, &res, nullptr
    );
    HandleReturnCode(rc, res.rc, "ServiceProxy::SetName()"sv);
}

Service::State ServiceProxy::GetState() const
{
    ::diode_Service_GetState_req req{};
    nk_req_reset(&req);

    ::diode_Service_GetState_res res{};

    const auto rc = ::diode_Service_GetState(
        &m_proxy.base, &req, nullptr, &res, nullptr
    );
    HandleReturnCode(rc, res.rc, "ServiceProxy::GetState()"sv);

    switch (res.state)
    {
    case diode_Service_ServiceStateStopped:
        return State::Stopped;
    case diode_Service_ServiceStateStarting:
        return State::Starting;
    case diode_Service_ServiceStateStarted:
        return State::Started;
    case diode_Service_ServiceStateStopping:
        return State::Stopping;
    case diode_Service_ServiceStateDefunct:
        return State::Defunct;
    }

    throw std::logic_error(
        "diode::ServiceProxy::GetState(): unknown state"
    );
}

Service::Status ServiceProxy::GetStatus() const
{
    ::diode_Service_GetStatus_req req{};
    nk_req_reset(&req);

    ::diode_Service_GetStatus_res res{};

    const auto rc = ::diode_Service_GetStatus(
        &m_proxy.base, &req, nullptr, &res, nullptr
    );
    HandleReturnCode(rc, res.rc, "ServiceProxy::GetStatus()"sv);

    switch (res.status)
    {
    case diode_Service_ServiceStatusOk:
        return Status::OK;
    case diode_Service_ServiceStatusFailedToStart:
        return Status::FailedToStart;
    case diode_Service_ServiceStatusFailedToRollback:
        return Status::FailedToRollback;
    case diode_Service_ServiceStatusFailedToStop:
        return Status::FailedToStop;
    case diode_Service_ServiceStatusFailedToOperate:
        return Status::FailedToOperate;
    }

    throw std::logic_error(
        "diode::ServiceProxy::GetStatus(): unknown status"
    );
}

void ServiceProxy::Start()
{
    ::diode_Service_Start_req req{};
    nk_req_reset(&req);

    ::diode_Service_Start_res res{};

    const auto rc = ::diode_Service_Start(
        &m_proxy.base, &req, nullptr, &res, nullptr
    );
    HandleReturnCode(rc, res.rc, "ServiceProxy::Start()"sv);
}

void ServiceProxy::Stop()
{
    ::diode_Service_Stop_req req{};
    nk_req_reset(&req);

    ::diode_Service_Stop_res res{};

    const auto rc = ::diode_Service_Stop(
        &m_proxy.base, &req, nullptr, &res, nullptr
    );
    HandleReturnCode(rc, res.rc, "ServiceProxy::Stop()"sv);
}

// static
void ServiceProxy::HandleReturnCode(const nk_err_t rc, const int resRc,
    std::string_view methodName)
{
    ExceptionHelper::HandleNkReturnCode(rc, resRc, methodName);
}

} // namespace diode

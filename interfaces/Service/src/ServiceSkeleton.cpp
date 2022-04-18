#include <ServiceSkeleton.hpp>

#include <cassert>

#include <utility>

#include <coresrv/nk/transport-kos.h>

#include <BaseException.hpp>

namespace diode
{

namespace
{
    extern const ::diode_Service_ops s_ops; // NOTE: Defined below.
}

ServiceSkeleton::ServiceSkeleton(std::shared_ptr<Service> impl)
    : m_skeleton{
        { &s_ops },
        std::move(impl)
    }
{}

static
nk_err_t _GetName(
    ::diode_Service* self,
    [[maybe_unused]] const ::diode_Service_GetName_req* req,
    [[maybe_unused]] const nk_arena* reqArena,
    ::diode_Service_GetName_res* res, nk_arena* resArena
) noexcept
try
{
    auto& impl = ServiceSkeleton::GetImpl(self);

    const auto name = impl.GetName();

    {
        auto rc = 0;

        assert(name.length() <= diode_Service_MaxServiceNameLength);
        rc = NkKosCopyStringToArena(resArena, &res->name, name.c_str());
        assert(rc == 0);
    }

    res->rc = diode_Service_ServiceStatusOk;

    return NK_EOK;
}
catch (const BaseException& e)
{
    res->rc = diode_Service_ServiceRetcodeBaseException;
    return NK_EOK;
}
catch (...)
{
    res->rc = diode_Service_ServiceRetcodeGeneric;
    return NK_EOK;
}

static
nk_err_t _SetName(
    ::diode_Service* self,
    const ::diode_Service_SetName_req* req, const nk_arena* reqArena,
    ::diode_Service_SetName_res* res, [[maybe_unused]] nk_arena* resArena
) noexcept
try
{
    auto& impl = ServiceSkeleton::GetImpl(self);

    auto name = std::string{};

    {
        nk_size_t reqNameLength = 0;
        nk_char_t* reqName = nk_arena_get(
            nk_char_t, reqArena,
            &req->name, &reqNameLength
        );
        assert(reqName != nullptr || reqNameLength == 0);
        assert(reqNameLength > 0);
        assert(reqNameLength <= diode_Service_MaxServiceNameLength);

        name.assign(reqName, reqNameLength - 1);
    }

    impl.SetName(name);

    res->rc = diode_Service_ServiceStatusOk;

    return NK_EOK;
}
catch (const BaseException& e)
{
    res->rc = diode_Service_ServiceRetcodeBaseException;
    return NK_EOK;
}
catch (...)
{
    res->rc = diode_Service_ServiceRetcodeGeneric;
    return NK_EOK;
}

static
nk_err_t _GetState(
    ::diode_Service* self,
    [[maybe_unused]] const ::diode_Service_GetState_req* req,
    [[maybe_unused]] const nk_arena* reqArena,
    ::diode_Service_GetState_res* res, [[maybe_unused]] nk_arena* resArena
) noexcept
try
{
    auto& impl = ServiceSkeleton::GetImpl(self);

    const auto state = impl.GetState();

    switch (state)
    {
    case Service::State::Stopped:
        res->state = diode_Service_ServiceStateStopped;
        break;
    case Service::State::Starting:
        res->state = diode_Service_ServiceStateStarting;
        break;
    case Service::State::Started:
        res->state = diode_Service_ServiceStateStarted;
        break;
    case Service::State::Stopping:
        res->state = diode_Service_ServiceStateStopping;
        break;
    case Service::State::Defunct:
        res->state = diode_Service_ServiceStateDefunct;
        break;
    }

    res->rc = diode_Service_ServiceStatusOk;

    return NK_EOK;
}
catch (const BaseException& e)
{
    res->rc = diode_Service_ServiceRetcodeBaseException;
    return NK_EOK;
}
catch (...)
{
    res->rc = diode_Service_ServiceRetcodeGeneric;
    return NK_EOK;
}

static
nk_err_t _GetStatus(
    ::diode_Service* self,
    [[maybe_unused]] const ::diode_Service_GetStatus_req* req,
    [[maybe_unused]] const nk_arena* reqArena,
    ::diode_Service_GetStatus_res* res, [[maybe_unused]] nk_arena* resArena
) noexcept
try
{
    auto& impl = ServiceSkeleton::GetImpl(self);

    const auto status = impl.GetStatus();

    switch (status)
    {
    case Service::Status::OK:
        res->status = diode_Service_ServiceStatusOk;
        break;
    case Service::Status::FailedToStart:
        res->status = diode_Service_ServiceStatusFailedToStart;
        break;
    case Service::Status::FailedToRollback:
        res->status = diode_Service_ServiceStatusFailedToRollback;
        break;
    case Service::Status::FailedToStop:
        res->status = diode_Service_ServiceStatusFailedToStop;
        break;
    case Service::Status::FailedToOperate:
        res->status = diode_Service_ServiceStatusFailedToOperate;
        break;
    }

    res->rc = diode_Service_ServiceStatusOk;

    return NK_EOK;
}
catch (const BaseException& e)
{
    res->rc = diode_Service_ServiceRetcodeBaseException;
    return NK_EOK;
}
catch (...)
{
    res->rc = diode_Service_ServiceRetcodeGeneric;
    return NK_EOK;
}

static
nk_err_t _Start(
    ::diode_Service* self,
    [[maybe_unused]] const ::diode_Service_Start_req* req,
    [[maybe_unused]] const nk_arena* reqArena,
    ::diode_Service_Start_res* res, [[maybe_unused]] nk_arena* resArena
) noexcept
try
{
    auto& impl = ServiceSkeleton::GetImpl(self);

    impl.Start();

    res->rc = diode_Service_ServiceStatusOk;

    return NK_EOK;
}
catch (const BaseException& e)
{
    res->rc = diode_Service_ServiceRetcodeBaseException;
    return NK_EOK;
}
catch (...)
{
    res->rc = diode_Service_ServiceRetcodeGeneric;
    return NK_EOK;
}

static
nk_err_t _Stop(
    ::diode_Service* self,
    [[maybe_unused]] const ::diode_Service_Stop_req* req,
    [[maybe_unused]] const nk_arena* reqArena,
    ::diode_Service_Stop_res* res, [[maybe_unused]] nk_arena* resArena
) noexcept
try
{
    auto& impl = ServiceSkeleton::GetImpl(self);

    impl.Stop();

    res->rc = diode_Service_ServiceStatusOk;

    return NK_EOK;
}
catch (const BaseException& e)
{
    res->rc = diode_Service_ServiceRetcodeBaseException;
    return NK_EOK;
}
catch (...)
{
    res->rc = diode_Service_ServiceRetcodeGeneric;
    return NK_EOK;
}

namespace
{
    const ::diode_Service_ops s_ops = {
        .GetName = _GetName,
        .SetName = _SetName,
        .GetState = _GetState,
        .GetStatus = _GetStatus,
        .Start = _Start,
        .Stop = _Stop,
    };
}

} // namespace diode

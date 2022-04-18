#include <ConsumerProxy.hpp>

#include <cassert>

#include <stdexcept>

#include <coresrv/nk/transport-kos.h>

#include <BaseException.hpp>
#include <ExceptionHelper.hpp>

using namespace std::string_view_literals;

namespace diode
{

ConsumerProxy::ConsumerProxy(
    nk_transport* transport, const nk_iid_t riid
)
    : m_reqArena{std::make_unique<ReqArenaBuffer>()}
    , m_resArena{std::make_unique<ResArenaBuffer>()}
{
    ::diode_Consumer_proxy_init(&m_proxy, transport, riid);
}

void ConsumerProxy::Consume(const DataItem& item)
{
    ::diode_Consumer_Consume_req req{};
    nk_req_reset(&req);
    auto& reqBuf = *m_reqArena;
    nk_arena reqArena = NK_ARENA_INITIALIZER(
        reqBuf.data(), reqBuf.data() + reqBuf.size()
    );

    {
        auto rc = 0;

        assert(item.value.length() <= 256); // TODO: Import from IDL.
        rc = NkKosCopyStringToArena(&reqArena, &req.item.value, item.value.c_str());
        assert(rc == 0);
    }

    ::diode_Consumer_Consume_res res{};

    const auto rc = ::diode_Consumer_Consume(
        &m_proxy.base, &req, &reqArena, &res, nullptr
    );
    HandleReturnCode(rc, res.rc, "Consumer::Consume()"sv);
}

// static
void ConsumerProxy::HandleReturnCode(const nk_err_t rc, const int resRc,
    std::string_view methodName)
{
    ExceptionHelper::HandleNkReturnCode(rc, resRc, methodName);
}

} // namespace diode

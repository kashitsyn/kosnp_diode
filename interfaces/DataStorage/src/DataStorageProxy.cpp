#include <DataStorageProxy.hpp>

#include <cassert>

#include <stdexcept>
#include <string>

#include <coresrv/nk/transport-kos.h>

#include <BaseException.hpp>
#include <ExceptionHelper.hpp>

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace diode
{

DataStorageProxy::DataStorageProxy(
    nk_transport* transport, const nk_iid_t riid)
    : m_reqArena{std::make_unique<ReqArenaBuffer>()}
    , m_resArena{std::make_unique<ResArenaBuffer>()}
{
    ::diode_DataStorage_proxy_init(&m_proxy, transport, riid);
}

std::optional<DataStorage::Value>
DataStorageProxy::Get(const Key& key) const
{
    ::diode_DataStorage_Get_req req{};
    nk_req_reset(&req);
    auto& reqBuf = *m_reqArena;
    nk_arena reqArena = NK_ARENA_INITIALIZER(
        reqBuf.data(), reqBuf.data() + reqBuf.size()
    );

    {
        auto rc = 0;

        assert(key.length() <= diode_DataStorage_MaxDataStorageKeyLength);
        rc = NkKosCopyStringToArena(&reqArena, &req.key, key.c_str());
        assert(rc == 0);
    }

    ::diode_DataStorage_Get_res res{};
    auto& resBuf = *m_resArena;
    nk_arena resArena = NK_ARENA_INITIALIZER(
        resBuf.data(), resBuf.data() + resBuf.size()
    );

    const auto rc = ::diode_DataStorage_Get(
        &m_proxy.base, &req, &reqArena, &res, &resArena
    );
    HandleReturnCode(rc, res.rc, "DataStorageProxy::Get()"sv);

    auto value = ""s;

    {
        nk_size_t resValueLength = 0;
        nk_char_t* resValue = nk_arena_get(
            nk_char_t, &resArena,
            &res.value, &resValueLength
        );
        assert(resValue != nullptr || resValueLength == 0);
        assert(resValueLength > 0);
        assert(resValueLength <= diode_DataStorage_MaxDataStorageValueLength);

        value.assign(resValue, resValueLength - 1);
    }

    switch (res.status)
    {
    case diode_DataStorage_DataStorageKeyStatusKeyNotInStorage:
        assert(value.empty());
        return {};
    case diode_DataStorage_DataStorageKeyStatusKeyInStorage:
        return value;
    }

    throw std::logic_error(
        "diode::DataStorageProxy::Get(): unknown status"
    );
}

// static
void DataStorageProxy::HandleReturnCode(const nk_err_t rc, const int resRc,
    std::string_view methodName)
{
    ExceptionHelper::HandleNkReturnCode(rc, resRc, methodName);
}

} // namespace diode

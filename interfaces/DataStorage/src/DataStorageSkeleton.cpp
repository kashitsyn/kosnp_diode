#include <DataStorageSkeleton.hpp>

#include <cassert>

#include <string>
#include <tuple>
#include <utility>

#include <coresrv/nk/transport-kos.h>

#include <BaseException.hpp>

using namespace std::string_literals;

namespace diode
{

namespace
{
    extern const ::diode_DataStorage_ops s_ops; // NOTE: Defined below.
}

DataStorageSkeleton::DataStorageSkeleton(std::shared_ptr<DataStorage> impl)
    : m_skeleton{
        { &s_ops },
        std::move(impl)
    }
{}

static
nk_err_t _Get(
    ::diode_DataStorage* self,
    const ::diode_DataStorage_Get_req* req, const nk_arena* reqArena,
    ::diode_DataStorage_Get_res* res, nk_arena* resArena
) noexcept
try
{
    auto& impl = DataStorageSkeleton::GetImpl(self);

    auto key = ""s;

    {
        nk_size_t reqKeyLength = 0;
        nk_char_t* reqKey = nk_arena_get(
            nk_char_t, reqArena,
            &req->key, &reqKeyLength
        );
        assert(reqKey != nullptr || reqKeyLength == 0);
        assert(reqKeyLength > 0);
        assert(reqKeyLength <= diode_DataStorage_MaxDataStorageKeyLength);

        key.assign(reqKey, reqKeyLength - 1);
    }

    const auto [hasValue, value] = [&] {
        const auto optValue = impl.Get(key);
        return std::tuple{
            optValue.has_value(),
            std::move(optValue).value_or(""s)
        };
    }();

    {
        auto rc = 0;

        assert(value.length() <= diode_DataStorage_MaxDataStorageValueLength);
        rc = NkKosCopyStringToArena(resArena, &res->value, value.c_str());
        assert(rc == 0);
    }

    res->status = hasValue ?
        diode_DataStorage_DataStorageKeyStatusKeyInStorage :
        diode_DataStorage_DataStorageKeyStatusKeyNotInStorage;

    res->rc = diode_DataStorage_DataStorageRetcodeOk;

    return NK_EOK;
}
catch (const BaseException& e)
{
    res->rc = diode_DataStorage_DataStorageRetcodeBaseException;
    return NK_EOK;
}
catch (...)
{
    res->rc = diode_DataStorage_DataStorageRetcodeGeneric;
    return NK_EOK;
}

namespace
{
    const ::diode_DataStorage_ops s_ops = {
        .Get = _Get,
    };
}

} // namespace diode

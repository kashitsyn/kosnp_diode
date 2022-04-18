#include <ConsumerSkeleton.hpp>

#include <cassert>

#include <utility>

#include <coresrv/nk/transport-kos.h>

#include <BaseException.hpp>

namespace diode
{

namespace
{
    extern const ::diode_Consumer_ops s_ops; // NOTE: Defined below.
}

ConsumerSkeleton::ConsumerSkeleton(
    std::shared_ptr<Consumer> impl
)
    : m_skeleton{
        { &s_ops },
        std::move(impl)
    }
{}

static
nk_err_t _Consume(
    ::diode_Consumer* self,
    const ::diode_Consumer_Consume_req* req, const nk_arena* reqArena,
    ::diode_Consumer_Consume_res* res,
    [[maybe_unused]] nk_arena* resArena
) noexcept
try
{
    auto& impl = ConsumerSkeleton::GetImpl(self);

    auto item = DataItem{};

    {
        nk_size_t reqValueLength = 0;
        nk_char_t* reqValue = nk_arena_get(
            nk_char_t, reqArena,
            &req->item.value, &reqValueLength
        );
        assert(reqValue != nullptr || reqValueLength == 0);
        assert(reqValueLength > 0);
        assert(reqValueLength <= 256); // TODO: Import from IDL.

        item.value.assign(reqValue, reqValueLength - 1);
    }

    impl.Consume(item);

    res->rc = diode_Consumer_ConsumerRetcodeOk;

    return NK_EOK;
}
catch (const BaseException& e)
{
    res->rc = diode_Consumer_ConsumerRetcodeBaseException;
    return NK_EOK;
}
catch (...)
{
    res->rc = diode_Consumer_ConsumerRetcodeGeneric;
    return NK_EOK;
}

namespace
{
    const ::diode_Consumer_ops s_ops = {
        .Consume = _Consume,
    };
}

} // namespace diode

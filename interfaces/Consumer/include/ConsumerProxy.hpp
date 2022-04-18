#ifndef DIODE_CONSUMER_PROXY_HPP
#define DIODE_CONSUMER_PROXY_HPP

#include <array>
#include <memory>
#include <string_view>

#include <diode/Consumer.idl.h>

#include <Consumer.hpp>

namespace diode
{

class ConsumerProxy : public virtual Consumer
{

public:

    explicit
    ConsumerProxy(nk_transport* transport, nk_iid_t riid);

    ~ConsumerProxy() override = default;

    ConsumerProxy(const ConsumerProxy&) = delete;
    ConsumerProxy& operator=(const ConsumerProxy&) = delete;

    ConsumerProxy(ConsumerProxy&&) = delete;
    ConsumerProxy& operator=(ConsumerProxy&&) = delete;

    void Consume(const DataItem& item) override;

private:

    static
    void HandleReturnCode(nk_err_t rc, int resRc, std::string_view methodName);

    template<std::size_t N>
    using ArenaBuffer = std::array<std::byte, N>;

    template<std::size_t N>
    using Arena = std::unique_ptr<ArenaBuffer<N>>;

    using ReqArenaBuffer = ArenaBuffer<::diode_Consumer_req_arena_size>;

    using ReqArena = Arena<::diode_Consumer_req_arena_size>;

    using ResArenaBuffer = ArenaBuffer<::diode_Consumer_res_arena_size>;

    using ResArena = Arena<::diode_Consumer_res_arena_size>;

    mutable ::diode_Consumer_proxy m_proxy{};
    ReqArena m_reqArena{};
    ResArena m_resArena{};

};

} // namespace diode

#endif // DIODE_CONSUMER_PROXY_HPP

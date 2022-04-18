#ifndef DIODE_SERVICE_PROXY_HPP
#define DIODE_SERVICE_PROXY_HPP

#include <array>
#include <memory>
#include <string_view>

#include <diode/Service.idl.h>

#include <Service.hpp>

namespace diode
{

class ServiceProxy : public virtual Service
{

public:

    explicit
    ServiceProxy(nk_transport* transport, nk_iid_t riid);

    ~ServiceProxy() override = default;

    ServiceProxy(const ServiceProxy&) = delete;
    ServiceProxy& operator=(const ServiceProxy&) = delete;

    ServiceProxy(ServiceProxy&&) = delete;
    ServiceProxy& operator=(ServiceProxy&&) = delete;

    // Service

    std::string GetName() const override;

    void SetName(std::string name) override;

    State GetState() const override;

    Status GetStatus() const override;

    void Start() override;

    void Stop() override;

private:

    static
    void HandleReturnCode(nk_err_t rc, int resRc, std::string_view methodName);

    template<std::size_t N>
    using ArenaBuffer = std::array<std::byte, N>;

    template<std::size_t N>
    using Arena = std::unique_ptr<ArenaBuffer<N>>;

    using ReqArenaBuffer = ArenaBuffer<::diode_Service_req_arena_size>;

    using ReqArena = Arena<::diode_Service_req_arena_size>;

    using ResArenaBuffer = ArenaBuffer<::diode_Service_res_arena_size>;

    using ResArena = Arena<::diode_Service_res_arena_size>;

    mutable ::diode_Service_proxy m_proxy{};
    ReqArena m_reqArena{};
    ResArena m_resArena{};

};

} // namespace diode

#endif // DIODE_SERVICE_PROXY_HPP

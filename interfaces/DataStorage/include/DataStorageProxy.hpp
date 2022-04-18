#ifndef DIODE_DATA_STORAGE_PROXY_HPP
#define DIODE_DATA_STORAGE_PROXY_HPP

#include <array>
#include <memory>
#include <string_view>

#include <diode/DataStorage.idl.h>

#include <DataStorage.hpp>

namespace diode
{

class DataStorageProxy : public virtual DataStorage
{

public:

    explicit
    DataStorageProxy(nk_transport* transport, nk_iid_t riid);

    ~DataStorageProxy() override = default;

    DataStorageProxy(const DataStorageProxy&) = delete;
    DataStorageProxy& operator=(const DataStorageProxy&) = delete;

    DataStorageProxy(DataStorageProxy&&) = delete;
    DataStorageProxy& operator=(DataStorageProxy&&) = delete;

    // DataStorage

    std::optional<Value> Get(const Key& key) const override;

private:

    static
    void HandleReturnCode(nk_err_t rc, int resRc, std::string_view methodName);

    template<std::size_t N>
    using ArenaBuffer = std::array<std::byte, N>;

    template<std::size_t N>
    using Arena = std::unique_ptr<ArenaBuffer<N>>;

    using ReqArenaBuffer = ArenaBuffer<::diode_DataStorage_req_arena_size>;

    using ReqArena = Arena<::diode_DataStorage_req_arena_size>;

    using ResArenaBuffer = ArenaBuffer<::diode_DataStorage_res_arena_size>;

    using ResArena = Arena<::diode_DataStorage_res_arena_size>;

    mutable ::diode_DataStorage_proxy m_proxy{};
    ReqArena m_reqArena{};
    ResArena m_resArena{};

};

} // namespace diode

#endif // DIODE_DATA_STORAGE_PROXY_HPP

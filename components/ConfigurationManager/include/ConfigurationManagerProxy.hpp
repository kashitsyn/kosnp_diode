#ifndef DIODE_CONFIGURATION_MANAGER_PROXY_HPP
#define DIODE_CONFIGURATION_MANAGER_PROXY_HPP

#include <memory>
#include <utility>

#include <diode/ConfigurationManager.cdl.h>

#include <DataStorageProxy.hpp>
#include <ConfigurationManager.hpp>
#include <NkKosTransport.hpp>

namespace diode
{

class ConfigurationManagerProxy
    : public ConfigurationManager
    , public DataStorageProxy
{

public:

    explicit
    ConfigurationManagerProxy(
        std::unique_ptr<NkKosTransport> transport
        , nk_iid_t dataStorageImplRiid
    )
        : ConfigurationManager{}
        , DataStorageProxy(transport->Get(), dataStorageImplRiid)
        , m_transport{std::move(transport)}
    {}

private:

    std::unique_ptr<NkKosTransport> m_transport{};

};

} // namespace diode

#endif // DIODE_CONFIGURATION_MANAGER_PROXY_HPP

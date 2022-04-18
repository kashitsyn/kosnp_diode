#ifndef DIODE_CONFIGURATION_MANAGER_IMPL_HPP
#define DIODE_CONFIGURATION_MANAGER_IMPL_HPP

#include <ConfigurationManagerImplFactory.hpp>

namespace diode
{

class ConfigurationManagerImpl
    : public ConfigurationManager
{

public:

    explicit
    ConfigurationManagerImpl() = default;

    // DataStorage

    std::optional<Value> Get(const Key& key) const override;

};

} // namespace diode

#endif // DIODE_CONFIGURATION_MANAGER_IMPL_HPP

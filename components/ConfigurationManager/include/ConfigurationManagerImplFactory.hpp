#ifndef DIODE_CONFIGURATION_MANAGER_IMPL_FACTORY_HPP
#define DIODE_CONFIGURATION_MANAGER_IMPL_FACTORY_HPP

#include <memory>
#include <string>

#include <ConfigurationManager.hpp>

namespace diode
{

struct ConfigurationManagerImplFactory
{

    std::unique_ptr<ConfigurationManager> operator()();

};

} // namespace diode

#endif // DIODE_CONFIGURATION_MANAGER_IMPL_FACTORY_HPP

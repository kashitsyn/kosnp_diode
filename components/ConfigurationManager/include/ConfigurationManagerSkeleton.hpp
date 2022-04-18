#ifndef DIODE_CONFIGURATION_MANAGER_SKELETON_HPP
#define DIODE_CONFIGURATION_MANAGER_SKELETON_HPP

#include <memory>

#include <diode/ConfigurationManager.cdl.h>

#include <DataStorageSkeleton.hpp>
#include <ConfigurationManager.hpp>

namespace diode
{

class ConfigurationManagerSkeleton
    : private DataStorageSkeleton
{

public:

    explicit
    ConfigurationManagerSkeleton(
        std::shared_ptr<ConfigurationManager> impl
    )
        : DataStorageSkeleton(impl)
    {
        ::diode_ConfigurationManager_component_init(
            &m_component
            , DataStorageSkeleton::GetSkeleton()
        );
    }

    auto GetComponent()
    {
        return &m_component;
    }

private:

    ::diode_ConfigurationManager_component m_component{};

};

} // namespace diode

#endif // DIODE_CONFIGURATION_MANAGER_SKELETON_HPP

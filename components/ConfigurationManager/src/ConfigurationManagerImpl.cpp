#include "ConfigurationManagerImpl.hpp"

#include <optional>

using namespace std::string_literals;

namespace diode
{

std::optional<DataStorage::Value>
ConfigurationManagerImpl::Get(const Key& key) const
{
    if (key == "ReceiverSettings"s)
    {
#ifdef __KOS__
        return "192.168.188.1:4000"s;
#else
        return "localhost:4000"s;
#endif
    }
    else if (key == "SenderSettings"s)
    {
        return "0.0.0.0:5000";
    }

    return std::nullopt;
}

std::unique_ptr<ConfigurationManager>
ConfigurationManagerImplFactory::operator()()
{
    return std::make_unique<ConfigurationManagerImpl>();
}

} // namespace diode

#ifndef DIODE_ANODE_CLIENT_IMPL_FACTORY_HPP
#define DIODE_ANODE_CLIENT_IMPL_FACTORY_HPP

#include <memory>
#include <string_view>

#include <AnodeClient.hpp>

namespace diode
{

struct AnodeClientImplFactory
{

    std::unique_ptr<AnodeClient> operator()(std::string_view serviceName);

};

} // namespace diode

#endif // DIODE_ANODE_CLIENT_IMPL_FACTORY_HPP

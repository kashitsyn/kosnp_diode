#ifndef DIODE_CATHODE_CLIENT_IMPL_FACTORY_HPP
#define DIODE_CATHODE_CLIENT_IMPL_FACTORY_HPP

#include <memory>
#include <string_view>

#include <CathodeClient.hpp>

namespace diode
{

struct CathodeClientImplFactory
{

    std::unique_ptr<CathodeClient> operator()(std::string_view serviceName);

};

} // namespace diode

#endif // DIODE_CATHODE_CLIENT_IMPL_FACTORY_HPP

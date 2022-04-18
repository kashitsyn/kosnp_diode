#ifndef DIODE_CATHODE_SERVER_IMPL_FACTORY_HPP
#define DIODE_CATHODE_SERVER_IMPL_FACTORY_HPP

#include <memory>
#include <string>
#include <string_view>

#include <TcpSender.hpp>
#include <CathodeServer.hpp>

namespace diode
{

struct CathodeServerImplFactory
{

    std::unique_ptr<CathodeServer>
    operator()(
        std::string name
        , std::string_view serviceName
        , std::shared_ptr<TcpSender> TcpSenderImpl
    );

};

} // namespace diode

#endif // DIODE_CATHODE_SERVER_IMPL_FACTORY_HPP

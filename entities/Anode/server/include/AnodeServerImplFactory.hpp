#ifndef DIODE_ANODE_SERVER_IMPL_FACTORY_HPP
#define DIODE_ANODE_SERVER_IMPL_FACTORY_HPP

#include <memory>
#include <string>
#include <string_view>

#include <TcpReceiver.hpp>
#include <AnodeServer.hpp>

namespace diode
{

struct AnodeServerImplFactory
{

    std::unique_ptr<AnodeServer>
    operator()(
        std::string name
        , std::string_view serviceName
        , std::shared_ptr<TcpReceiver> TcpReceiverImpl
        , std::shared_ptr<ConfigurationManager> configurationManagerImpl
    );

};

} // namespace diode

#endif // DIODE_ANODE_SERVER_IMPL_FACTORY_HPP

#ifndef DIODE_ANODE_CLIENT_HPP
#define DIODE_ANODE_CLIENT_HPP

#include <ConfigurationManager.hpp>
#include <TcpReceiver.hpp>

namespace diode
{

struct AnodeClient
{

    virtual
    ~AnodeClient() = default;

    virtual
    std::unique_ptr<ConfigurationManager>
    GetConfigurationManager() = 0;

    virtual
    std::shared_ptr<TcpReceiver>
    GetTcpReceiver() const = 0;

};

} // namespace diode

#endif // DIODE_ANODE_CLIENT_HPP

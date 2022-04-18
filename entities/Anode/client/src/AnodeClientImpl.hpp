#ifndef DIODE_ANODE_CLIENT_IMPL_HPP
#define DIODE_ANODE_CLIENT_IMPL_HPP

#include <handle/handletype.h>

#include <ConfigurationManagerProxy.hpp>
#include <TcpReceiverProxy.hpp>
#include <AnodeClientImplFactory.hpp>

namespace diode
{

class AnodeClientImpl : public AnodeClient
{

public:

    explicit
    AnodeClientImpl(std::string_view serviceName);

    virtual
    ~AnodeClientImpl() = default;

    std::unique_ptr<ConfigurationManager>
    GetConfigurationManager()
    {
        return std::move(m_configurationManagerProxy);
    }

    std::shared_ptr<TcpReceiver>
    GetTcpReceiver() const
    {
        return m_tcpReceiverProxy;
    }

private:

    Handle m_handle = INVALID_HANDLE;

    std::unique_ptr<ConfigurationManagerProxy> m_configurationManagerProxy{};
    std::shared_ptr<TcpReceiverProxy> m_tcpReceiverProxy{};

};

} // namespace diode

#endif // DIODE_ANODE_CLIENT_IMPL_HPP

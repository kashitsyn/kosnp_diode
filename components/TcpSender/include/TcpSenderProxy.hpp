#ifndef DIODE_TCP_SENDER_PROXY_HPP
#define DIODE_TCP_SENDER_PROXY_HPP

#include <memory>
#include <utility>

#include <NkKosTransport.hpp>
#include <ServiceProxy.hpp>

#include <TcpSender.hpp>
#include <ConsumerProxy.hpp>

namespace diode
{

class TcpSenderProxy
    : public TcpSender
    , public ServiceProxy
    , public ConsumerProxy
{

public:

    explicit
    TcpSenderProxy(
        std::unique_ptr<NkKosTransport> transport
        , nk_iid_t serviceImplRiid
        , nk_iid_t sendingHubManagerImplRiid
    )
        : TcpSender{}
        , ServiceProxy(transport->Get(), serviceImplRiid)
        , ConsumerProxy(transport->Get(), sendingHubManagerImplRiid)
        , m_transport{std::move(transport)}
    {}

private:

    std::unique_ptr<NkKosTransport> m_transport{};

};

} // namespace diode

#endif // DIODE_TCP_SENDER_PROXY_HPP

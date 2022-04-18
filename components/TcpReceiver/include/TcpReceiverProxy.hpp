#ifndef DIODE_TCP_RECEIVER_PROXY_HPP
#define DIODE_TCP_RECEIVER_PROXY_HPP

#include <memory>
#include <utility>

#include <NkKosTransport.hpp>
#include <ServiceProxy.hpp>

#include <diode/TcpReceiver.cdl.h>

#include <TcpReceiver.hpp>

namespace diode
{

class TcpReceiverProxy
    : public TcpReceiver
    , public ServiceProxy
{

public:

    explicit
    TcpReceiverProxy(
        std::unique_ptr<NkKosTransport> transport
        , nk_iid_t serviceImplRiid
    )
        : TcpReceiver{}
        , ServiceProxy(transport->Get(), serviceImplRiid)
        , m_transport{std::move(transport)}
    {}

private:

    std::unique_ptr<NkKosTransport> m_transport{};

};

} // namespace diode

#endif // DIODE_TCP_RECEIVER_PROXY_HPP

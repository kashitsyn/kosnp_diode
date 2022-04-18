#ifndef DIODE_TCP_RECEIVER_SKELETON_HPP
#define DIODE_TCP_RECEIVER_SKELETON_HPP

#include <memory>

#include <ServiceSkeleton.hpp>

#include <diode/TcpReceiver.cdl.h>

#include <TcpReceiver.hpp>

namespace diode
{

class TcpReceiverSkeleton
    : private ServiceSkeleton
{

public:

    explicit
    TcpReceiverSkeleton(
        std::shared_ptr<TcpReceiver> impl
    )
        : ServiceSkeleton(impl)
    {
        ::diode_TcpReceiver_component_init(
            &m_component
            , ServiceSkeleton::GetSkeleton()
        );
    }

    auto GetComponent()
    {
        return &m_component;
    }

private:

    ::diode_TcpReceiver_component m_component{};

};

} // namespace diode

#endif // DIODE_TCP_RECEIVER_SKELETON_HPP

#ifndef DIODE_TCP_SENDER_SKELETON_HPP
#define DIODE_TCP_SENDER_SKELETON_HPP

#include <memory>

#include <ServiceSkeleton.hpp>

#include <TcpSender.hpp>
#include <ConsumerSkeleton.hpp>

namespace diode
{

class TcpSenderSkeleton
    : private ServiceSkeleton
    , private ConsumerSkeleton
{

public:

    explicit
    TcpSenderSkeleton(
        std::shared_ptr<TcpSender> impl
    )
        : ServiceSkeleton(impl)
        , ConsumerSkeleton(impl)
    {
        ::diode_TcpSender_component_init(
            &m_component
            , ServiceSkeleton::GetSkeleton()
            , ConsumerSkeleton::GetSkeleton()
        );
    }

    auto GetComponent()
    {
        return &m_component;
    }

private:

    ::diode_TcpSender_component m_component{};

};

} // namespace diode

#endif // DIODE_TCP_SENDER_SKELETON_HPP

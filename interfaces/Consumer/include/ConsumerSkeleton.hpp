#ifndef DIODE_CONSUMER_SKELETON_HPP
#define DIODE_CONSUMER_SKELETON_HPP

#include <memory>

#include <diode/Consumer.idl.h>

#include <Consumer.hpp>

namespace diode
{

class ConsumerSkeleton
{

    struct Skeleton
    {
        ::diode_Consumer base;
        std::shared_ptr<Consumer> impl;
    };

public:

    explicit
    ConsumerSkeleton(std::shared_ptr<Consumer> impl);

    ~ConsumerSkeleton() = default;

    ConsumerSkeleton(const ConsumerSkeleton&) = delete;
    ConsumerSkeleton&
    operator=(const ConsumerSkeleton&) = delete;

    ConsumerSkeleton(ConsumerSkeleton&&) = delete;
    ConsumerSkeleton&
    operator=(ConsumerSkeleton&&) = delete;

    ::diode_Consumer* GetSkeleton()
    {
        return &m_skeleton.base;
    }

    static
    auto& GetImpl(::diode_Consumer* self)
    {
        return *reinterpret_cast<Skeleton*>(self)->impl;
    }

private:

    Skeleton m_skeleton;

};

} // namespace diode

#endif // DIODE_CONSUMER_SKELETON_HPP

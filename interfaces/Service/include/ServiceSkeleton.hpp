#ifndef DIODE_SERVICE_SKELETON_HPP
#define DIODE_SERVICE_SKELETON_HPP

#include <memory>

#include <diode/Service.idl.h>

#include <Service.hpp>

namespace diode
{

class ServiceSkeleton
{

    struct Skeleton
    {
        ::diode_Service base;
        std::shared_ptr<Service> impl;
    };

public:

    explicit
    ServiceSkeleton(std::shared_ptr<Service> impl);

    ~ServiceSkeleton() = default;

    ServiceSkeleton(const ServiceSkeleton&) = delete;
    ServiceSkeleton& operator=(const ServiceSkeleton&) = delete;

    ServiceSkeleton(ServiceSkeleton&&) = delete;
    ServiceSkeleton& operator=(ServiceSkeleton&&) = delete;

    ::diode_Service* GetSkeleton()
    {
        return &m_skeleton.base;
    }

    static
    auto& GetImpl(::diode_Service* self)
    {
        return *reinterpret_cast<Skeleton*>(self)->impl;
    }

private:

    Skeleton m_skeleton;

};

} // namespace diode

#endif // DIODE_SERVICE_SKELETON_HPP

#ifndef DIODE_DATA_STORAGE_SKELETON_HPP
#define DIODE_DATA_STORAGE_SKELETON_HPP

#include <memory>

#include <diode/DataStorage.idl.h>

#include <DataStorage.hpp>

namespace diode
{

class DataStorageSkeleton
{

    struct Skeleton
    {
        ::diode_DataStorage base;
        std::shared_ptr<DataStorage> impl;
    };

public:

    explicit
    DataStorageSkeleton(std::shared_ptr<DataStorage> impl);

    ~DataStorageSkeleton() = default;

    DataStorageSkeleton(const DataStorageSkeleton&) = delete;
    DataStorageSkeleton& operator=(const DataStorageSkeleton&) = delete;

    DataStorageSkeleton(DataStorageSkeleton&&) = delete;
    DataStorageSkeleton& operator=(DataStorageSkeleton&&) = delete;

    ::diode_DataStorage* GetSkeleton()
    {
        return &m_skeleton.base;
    }

    static
    auto& GetImpl(::diode_DataStorage* self)
    {
        return *reinterpret_cast<Skeleton*>(self)->impl;
    }

private:

    Skeleton m_skeleton;

};

} // namespace diode

#endif // DIODE_DATA_STORAGE_SKELETON_HPP

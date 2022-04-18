#ifndef DIODE_DATA_STORAGE_HPP
#define DIODE_DATA_STORAGE_HPP

#include <optional>
#include <string>
#include <vector>

namespace diode
{

struct DataStorage
{

    using Key = std::string;
    using Value = std::string;

    virtual
    ~DataStorage() = default;

    virtual
    std::optional<Value> Get(const Key& key) const = 0;

};

} // namespace diode

#endif // DIODE_DATA_STORAGE_HPP

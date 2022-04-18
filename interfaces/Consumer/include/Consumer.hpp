#ifndef DIODE_CONSUMER_HPP
#define DIODE_CONSUMER_HPP

#include <vector>

#include <DataItem.hpp>

namespace diode
{

struct Consumer
{

    virtual
    ~Consumer() = default;

    virtual
    void Consume(const DataItem& item) = 0;

};

} // namespace diode

#endif // DIODE_CONSUMER_HPP

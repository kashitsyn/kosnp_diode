#ifndef DIODE_DATA_ITEM_HPP
#define DIODE_DATA_ITEM_HPP

#include <string>

namespace diode
{

struct DataItem
{

    constexpr static auto MaxValueLength = 256;

    std::string value;

};

} // namespace diode

#endif // DIODE_DATA_ITEM_HPP

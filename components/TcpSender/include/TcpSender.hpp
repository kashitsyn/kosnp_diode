#ifndef DIODE_TCP_SENDER_HPP
#define DIODE_TCP_SENDER_HPP

#include <Service.hpp>

#include <Consumer.hpp>

namespace diode
{

struct TcpSender
    : virtual Service
    , virtual Consumer
{};

} // namespace diode

#endif // DIODE_TCP_SENDER_HPP

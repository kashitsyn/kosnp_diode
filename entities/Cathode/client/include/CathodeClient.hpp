#ifndef DIODE_CATHODE_CLIENT_HPP
#define DIODE_CATHODE_CLIENT_HPP

#include <TcpSender.hpp>

namespace diode
{

struct CathodeClient
{

    virtual
    ~CathodeClient() = default;

    virtual
    std::shared_ptr<TcpSender>
    GetTcpSender() const = 0;

};

} // namespace diode

#endif // DIODE_CATHODE_CLIENT_HPP

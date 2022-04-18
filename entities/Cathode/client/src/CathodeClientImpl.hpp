#ifndef DIODE_CATHODE_CLIENT_IMPL_HPP
#define DIODE_CATHODE_CLIENT_IMPL_HPP

#include <handle/handletype.h>

#include <TcpSenderProxy.hpp>
#include <CathodeClientImplFactory.hpp>

namespace diode
{

class CathodeClientImpl : public CathodeClient
{

public:

    explicit
    CathodeClientImpl(std::string_view serviceName);

    std::shared_ptr<TcpSender>
    GetTcpSender() const
    {
        return m_TcpSenderProxy;
    }

private:

    Handle m_handle = INVALID_HANDLE;

    std::shared_ptr<TcpSenderProxy> m_TcpSenderProxy{};

};

} // namespace diode

#endif // DIODE_CATHODE_CLIENT_IMPL_HPP

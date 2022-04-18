#ifndef DIODE_KOS_BASE_PROXY_HPP
#define DIODE_KOS_BASE_PROXY_HPP

#include <coresrv/nk/transport-kos.h>

namespace diode
{

class NkKosTransport
{

public:

    explicit
    NkKosTransport(const Handle handle)
    {
        NkKosTransport_Init(&m_transport, handle, NK_NULL, 0);
    }

    ~NkKosTransport() = default;

    NkKosTransport(const NkKosTransport&) = delete;
    NkKosTransport& operator=(const NkKosTransport&) = delete;

    NkKosTransport(NkKosTransport&&) = delete;
    NkKosTransport& operator=(NkKosTransport&&) = delete;

    const nk_transport* Get() const
    {
        return &m_transport.base;
    }

    nk_transport* Get()
    {
        return &m_transport.base;
    }

private:

    ::NkKosTransport m_transport{};

};

} // namespace diode

#endif // DIODE_KOS_BASE_PROXY_HPP

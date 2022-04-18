#include "InterrupterImpl.hpp"

#include <cstring>

#include <iostream>

#include <InterrupterException.hpp>

namespace diode
{

InterrupterImpl::SingleInterrupterContext::SingleInterrupterContext()
{
    // NOTE: pthread_sigmask() will check signal mask, so we don't need to check it while creating.
    sigemptyset(&m_signalMask);
    sigaddset(&m_signalMask, SIGINT);
    sigaddset(&m_signalMask, SIGTERM);

    const auto rc = pthread_sigmask(SIG_BLOCK, &m_signalMask, nullptr);
    if (rc)
    {
        std::cerr << "Error: Failed to change signal mask: " << strerror(rc) << std::endl;
        throw InterrupterException();
    }
}

void InterrupterImpl::SingleInterrupterContext::Wait() const
{
    auto sig = int{};
    const auto rc = sigwait(&m_signalMask, &sig);
    if (rc)
    {
        std::cerr << "Error: Failed to wait interruption signals: " << strerror(rc) << std::endl;
        throw InterrupterException();
    }
}

std::unique_ptr<Interrupter>
InterrupterImplFactory::operator()()
{
    return std::make_unique<InterrupterImpl>();
}

} // namespace diode

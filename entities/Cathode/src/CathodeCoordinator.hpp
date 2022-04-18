#ifndef DIODE_CATHODE_COORDINATOR_HPP
#define DIODE_CATHODE_COORDINATOR_HPP

#include <memory>

namespace diode
{

class CathodeCoordinator
{

public:

    explicit
    CathodeCoordinator();

    ~CathodeCoordinator();

    // Coordinator

    void OnStartup();

    void Wait() const;

    void OnShutdown();

private:

    class Impl;
    std::unique_ptr<Impl> m_impl;

};

} // namespace diode

#endif // DIODE_CATHODE_COORDINATOR_HPP

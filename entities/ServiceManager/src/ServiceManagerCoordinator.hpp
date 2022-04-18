#ifndef DIODE_MAIN_COORDINATOR_HPP
#define DIODE_MAIN_COORDINATOR_HPP

#include <memory>

namespace diode
{

class ServiceManagerCoordinator
{

public:

    explicit
    ServiceManagerCoordinator();

    ~ServiceManagerCoordinator();

    // Coordinator

    void OnStartup();

    void Wait() const;

    void OnShutdown();

private:

    class Impl;
    std::unique_ptr<Impl> m_impl;

};

} // namespace diode

#endif // DIODE_MAIN_COORDINATOR_HPP

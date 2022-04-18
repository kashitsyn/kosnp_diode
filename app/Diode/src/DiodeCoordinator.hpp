#ifndef DIODE_APP_DIODE_COORDINATOR_HPP
#define DIODE_APP_DIODE_COORDINATOR_HPP

#include <memory>

namespace diode::app
{

class DiodeCoordinator
{

public:

    explicit
    DiodeCoordinator();

    ~DiodeCoordinator();

    // Coordinator

    void OnStartup();

    void Wait() const;

    void OnShutdown();

private:

    class Impl;
    std::unique_ptr<Impl> m_impl;

};

} // namespace diode::app

#endif // DIODE_APP_DIODE_COORDINATOR_HPP

#ifndef DIODE_ANODE_COORDINATOR_HPP
#define DIODE_ANODE_COORDINATOR_HPP

#include <memory>

namespace diode
{

class AnodeCoordinator
{

public:

    explicit
    AnodeCoordinator();

    ~AnodeCoordinator();

    // Coordinator

    void OnStartup();

    void Wait() const;

    void OnShutdown();

private:

    class Impl;
    std::unique_ptr<Impl> m_impl;

};

} // namespace diode

#endif // DIODE_ANODE_COORDINATOR_HPP

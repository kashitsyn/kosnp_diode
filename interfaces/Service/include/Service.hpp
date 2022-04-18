#ifndef DIODE_SERVICE_HPP
#define DIODE_SERVICE_HPP

#include <string>

namespace diode
{

struct Service
{

    enum class State
    {
        Stopped,
        Starting,
        Started,
        Stopping,
        Defunct,
    };

    enum class Status
    {
        OK,
        FailedToStart,
        FailedToRollback,
        FailedToStop,
        FailedToOperate,
    };

    virtual
    ~Service() = default;

    virtual
    std::string GetName() const = 0;

    virtual
    void SetName(std::string name) = 0;

    virtual
    State GetState() const = 0;

    virtual
    Status GetStatus() const = 0;

    virtual
    void Start() = 0;

    virtual
    void Stop() = 0;

};

} // namespace diode

#endif // DIODE_SERVICE_HPP

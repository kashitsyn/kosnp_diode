#ifndef DIODE_INTERRUPTER_HPP
#define DIODE_INTERRUPTER_HPP

namespace diode
{

struct Interrupter
{

    virtual
    ~Interrupter() = default;

    virtual
    void Wait() const = 0;

};

} // namespace diode

#endif // DIODE_INTERRUPTER_HPP

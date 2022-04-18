#ifndef DIODE_INTERRUPTER_IMPL_FACTORY_HPP
#define DIODE_INTERRUPTER_IMPL_FACTORY_HPP

#include <memory>

#include <Interrupter.hpp>

namespace diode
{

struct InterrupterImplFactory
{

    std::unique_ptr<Interrupter> operator()();

};

} // namespace diode

#endif // DIODE_INTERRUPTER_IMPL_FACTORY_HPP

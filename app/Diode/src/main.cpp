#include <Runner.hpp>

#include "DiodeCoordinator.hpp"

int main()
{
    return diode::Runner<diode::app::DiodeCoordinator>::Run();
}

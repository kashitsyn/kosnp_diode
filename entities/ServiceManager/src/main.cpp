#include <Runner.hpp>

#include "ServiceManagerCoordinator.hpp"

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <platform/platform.h>

#include <kos_net.h>

int main()
{
    if (!configure_net_iface(DEFAULT_INTERFACE, "192.168.188.8", DEFAULT_MASK, "192.168.188.1", DEFAULT_MTU)) {
        perror(DEFAULT_INTERFACE ": network iface configuration failed\n");
        return EXIT_FAILURE;
    }

    if (!list_network_ifaces()) {
        perror("listing of host network interfaces fails\n");
        return EXIT_FAILURE;
    }

    return diode::Runner<diode::ServiceManagerCoordinator>::Run();
}

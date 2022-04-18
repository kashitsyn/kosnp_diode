#include <env/env.h>

#include <stdlib.h>

#include <vfs/rumpfs_client.h>
#include <vfs/vfs.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    const char* NetVfsArgs[] = {
        "-l", "devfs /dev devfs 0"
    };
    const char* NetVfsEnvs[] = {
        "_VFS_NETWORK_BACKEND=server:VFS1",
        "_VFS_FILESYSTEM_BACKEND=server:VFS1"
    };
    ENV_REGISTER_PROGRAM_ENVIRONMENT("NetVfs", NetVfsArgs, NetVfsEnvs);

    const char* ServiceManagerEnvs[] = { "_VFS_NETWORK_BACKEND=client:VFS1", "_VFS_FILESYSTEM_BACKEND=client:VFS1" };
    ENV_REGISTER_VARS("ServiceManager", ServiceManagerEnvs);

    const char* CathodeEnvs[] = { "_VFS_NETWORK_BACKEND=client:VFS1", "_VFS_FILESYSTEM_BACKEND=client:VFS1" };
    ENV_REGISTER_VARS("Cathode", CathodeEnvs);

    const char* AnodeEnvs[] = { "_VFS_NETWORK_BACKEND=client:VFS1", "_VFS_FILESYSTEM_BACKEND=client:VFS1" };
    ENV_REGISTER_VARS("Anode", AnodeEnvs);

    // Starting up server

    envServerRun();

    return EXIT_SUCCESS;
}

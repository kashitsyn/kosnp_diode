#include <coresrv/fs/fs_api.h>
#include <coresrv/handle/handle_api.h>
#include <services/fs/FS.idl.h>

#define _VFS_SERVER_INTERFACE
#include <vfs/basic.h>

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mount.h>

static const char LogPrefix[] = "[VFS]";

static _vfs_server_thread_routine_t threadRoutine;
static void *threadRoutineArg;

void _vfs_server_set_main_thread_routine(_vfs_server_thread_routine_t func, void *arg)
{
    threadRoutine = func;
    threadRoutineArg = arg;
}

static bool processCfgLine(char *line)
{
    char *devname = strtok(line, " ");

    if (devname == NULL || strlen(devname) == 0)
    {
        fprintf(stderr, "%s Failed to read devname\n", LogPrefix);
        return false;
    }

    char *dirname = strtok(NULL, " ");

    if (dirname == NULL || strlen(dirname) == 0)
    {
        fprintf(stderr, "%s Failed to read dirname\n", LogPrefix);
        return false;
    }

    char *fsname = strtok(NULL, " ");

    if (fsname == NULL || strlen(fsname) == 0)
    {
        fprintf(stderr, "%s Failed to read fstype\n", LogPrefix);
        return false;
    }

    char *beginflags = strtok(NULL, " ");

    if (beginflags == NULL || strlen(beginflags) == 0)
    {
        fprintf(stderr, "%s Failed to read flags\n", LogPrefix);
        return false;
    }

#if defined(__arm__)
    long unsigned int flags = (long unsigned int)strtol(beginflags, NULL, 10);
#else
    int flags = (int)strtol(beginflags, NULL, 10);
#endif
    char *options = strtok(NULL, " ");

    if (options == NULL)
    {
        options = "";
    }

    int err = mkdir(dirname, S_IRWXU | S_IRWXG | S_IRWXO);
    if (err != 0 && errno != EEXIST)
    {
        fprintf(stderr, "%s Failed to mkdir %s\n", LogPrefix, dirname);
        return false;
    }

    if (err == 0) {
        sync();
    }

    if (mount(devname, dirname, fsname, flags, options) != 0)
    {
        fprintf(stderr, "%s Failed to mount %s, %s, %s\n",
                LogPrefix, devname, dirname, fsname);
        perror("ERROR mount");
        fflush(stderr);
        return false;
    }

    return true;
}

static void parseArgs(int argc, char *const argv[])
{
    int ch = 0;

    while ((ch = getopt(argc, argv, "l:")) != -1)
    {
        switch (ch) {
        case 'l':
            processCfgLine(optarg);
            break;
        }
    }
}

int main(int argc, char *const argv[])
{
    printf("%s %s started\n", LogPrefix, argv[0]);

    fflush(stdout);

    parseArgs(argc, argv);

    if (threadRoutine == NULL)
    {
        fprintf(stderr, "%s Failed to initialize thread routine\n", LogPrefix);
        return EXIT_FAILURE;
    }

    (*threadRoutine)(threadRoutineArg);

    return EXIT_SUCCESS;
}

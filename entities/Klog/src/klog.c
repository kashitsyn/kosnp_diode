#include <stddef.h>
#include <stdlib.h>

#include <nglog/nglog.h>

#include <klog/system_audit.h>
#include <klog_storage/client.h>

#include <klog/Klog.edl.h>

int main()
{
    nglog_init("klog", NGLOG_FOREGROUND, NGLOG_VERBOSE);

    return klog_system_audit_run(
        KLOG_SERVER_CONNECTION_ID ":" KLOG_STORAGE_SERVER_CONNECTION_ID,
        klog_Klog_klog_audit_iid
    );
}

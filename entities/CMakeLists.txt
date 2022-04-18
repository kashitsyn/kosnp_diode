include(platform/nk)

# NOTE: System-level entities.
add_subdirectory(Env)
add_subdirectory(Klog)
add_subdirectory(KlogStorage)
add_subdirectory(NetVfs)

# NOTE: Domain-level entities.
add_subdirectory(Anode)
add_subdirectory(Cathode)
add_subdirectory(ServiceManager)

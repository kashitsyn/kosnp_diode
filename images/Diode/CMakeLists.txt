project(einit)

include(platform/image)

include (platform/nk)

find_package(vfs REQUIRED)
include_directories(${vfs_INCLUDE})

find_package(kss REQUIRED)

find_package (klog REQUIRED)
include_directories (${klog_INCLUDE})

find_package (klog_storage REQUIRED)
include_directories (${klog_storage_INCLUDE})

set_target_properties(ServiceManager PROPERTIES ${vfs_ENTITY}_REPLACEMENT "")
set_target_properties(Cathode PROPERTIES ${vfs_ENTITY}_REPLACEMENT "")
set_target_properties(Anode PROPERTIES ${vfs_ENTITY}_REPLACEMENT "")

project_header_default ("STANDARD_GNU_11:YES" "STRICT_WARNINGS:NO")

set(ENTITIES
  Env
  ServiceManager
  Cathode
  Anode
  NetVfs
  KlogStorage
)

set(CONNECTIONS_CFG src/init.yaml.in)

set(SECURITY_PSL_FILE src/security.psl)

include_directories(
  ${CMAKE_SOURCE_DIR}/entities/Anode/include
  ${CMAKE_SOURCE_DIR}/entities/Cathode/include
)

set(INIT_Klog_PATH "KlogHw")

build_kos_hw_image(kos-image
  EINIT_ENTITY EinitHw
  CONNECTIONS_CFG ${CONNECTIONS_CFG}
  SECURITY_PSL ${SECURITY_PSL_FILE}
  KLOG_ENTITY KlogHw
  IMAGE_FILES ${ENTITIES}
)
target_link_libraries (KlogHw kssaudit)
add_dependencies(EinitHw klog-edl)
target_compile_options(EinitHw PRIVATE -w)
target_compile_options(EinitHw-edl PRIVATE -w)

set(INIT_Klog_PATH "KlogQemu")

build_kos_qemu_image(kos-qemu-image
  EINIT_ENTITY EinitQemu
  CONNECTIONS_CFG ${CONNECTIONS_CFG}
  SECURITY_PSL ${SECURITY_PSL_FILE}
  KLOG_ENTITY KlogQemu
  QEMU_FLAGS ${DEMO_QEMU_FLAGS}
  IMAGE_FILES ${ENTITIES}
)
target_link_libraries (KlogQemu kssaudit)
add_dependencies(EinitQemu klog-edl)
target_compile_options(EinitQemu PRIVATE -w)
target_compile_options(EinitQemu-edl PRIVATE -w)

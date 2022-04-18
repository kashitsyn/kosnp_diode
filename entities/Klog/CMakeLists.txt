project(klog)

set(TARGET_NAME Klog)

find_package(klog REQUIRED)
find_package(nglog REQUIRED)

set(CMAKE_C_STANDARD 11)

build_entity(${TARGET_NAME} EDL_FILES "include/Klog.edl")
add_custom_target(klog-edl
  DEPENDS ${EDL_FILES}
)

set(SRCS
  src/klog.c
  ${EDL_FILES}
)
foreach(src ${SRCS})
  get_filename_component(ABSOLUTE_PATH
    ${src} ABSOLUTE
  )
  list(APPEND TEMP_SRCS
    ${ABSOLUTE_PATH}
  )
endforeach()
set(SRCS ${TEMP_SRCS})
unset(TEMP_SRCS)

set(LIBS_PRIV
  ${klog_SYSTEM_AUDIT_LIB}
  ${nglog_LIBRARY}
)

set(LIBS_PUB
)

set(DIRS_PRIV
  ${CMAKE_CURRENT_BINARY_DIR}/src
  ${klog_INCLUDE}
  ${nglog_INCLUDE}
)

set(DIRS_PUB
)

set(DEFS_PRIV
)

set(DEFS_PUB
)

# QEMU
set(TARGET_NAME KlogHw)

add_executable(${TARGET_NAME} ${SRCS})

target_link_libraries(${TARGET_NAME}
  ${LIBS_PRIV}
  ${LIBS_PUB}
)

target_include_directories(${TARGET_NAME}
  PRIVATE ${DIRS_PRIV}
  PUBLIC ${DIRS_PUB}
)

target_compile_definitions(${TARGET_NAME}
  PRIVATE ${DEFS_PRIV}
  PUBLIC ${DEFS_PUB}
)

# QEMU
set(TARGET_NAME KlogQemu)

add_executable(${TARGET_NAME} ${SRCS})

target_link_libraries(${TARGET_NAME}
  ${LIBS_PRIV}
  ${LIBS_PUB}
)

target_include_directories(${TARGET_NAME}
  PRIVATE ${DIRS_PRIV}
  PUBLIC ${DIRS_PUB}
)

target_compile_definitions(${TARGET_NAME}
  PRIVATE ${DEFS_PRIV}
  PUBLIC ${DEFS_PUB}
)

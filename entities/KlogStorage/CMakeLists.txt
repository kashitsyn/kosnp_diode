project(klog)

set(TARGET_NAME KlogStorage)

find_package(klog_storage REQUIRED)
find_package(nglog REQUIRED)

set(CMAKE_C_STANDARD 11)

build_entity(${TARGET_NAME} EDL_FILES "include/KlogStorage.edl")

set(SRCS
  src/main.c
  ${EDL_FILES}
)

set(LIBS_PRIV
  ${klog_storage_SERVER_LIB}
  ${nglog_LIBRARY}
)

set(LIBS_PUB
)

set(DIRS_PRIV
  ${CMAKE_CURRENT_BINARY_DIR}/src
  ${klog_storage_INCLUDE}
  ${nglog_INCLUDE}
)

set(DIRS_PUB
)

set(DEFS_PRIV
)

set(DEFS_PUB
)

add_executable(${TARGET_NAME} ${SRCS})

target_link_libraries(${TARGET_NAME}
  PRIVATE ${LIBS_PRIV}
  PUBLIC ${LIBS_PUB}
)

target_include_directories(${TARGET_NAME}
  PRIVATE ${DIRS_PRIV}
  PUBLIC ${DIRS_PUB}
)

target_compile_definitions(${TARGET_NAME}
  PRIVATE ${DEFS_PRIV}
  PUBLIC ${DEFS_PUB}
)

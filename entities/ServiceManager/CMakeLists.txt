set(TARGET_NAME ServiceManager)

find_package(vfs REQUIRED)

set(CMAKE_CXX_STANDARD 17)

build_entity(${TARGET_NAME}
  EDL_FILES include/ServiceManager.edl
)

set(SRCS
  src/ServiceManagerCoordinator.cpp
  src/ServiceManagerCoordinator.hpp
  src/main.cpp
  ${EDL_FILES}
)

set(LIBS_PRIV
  DiodeServiceManager
  DiodeRunner
  DiodeThreading
  DiodeAnodeClient
  DiodeCathodeClient
  ${vfs_CLIENT_LIB}
)

set(LIBS_PUB
)

set(DIRS_PRIV
)

set(DIRS_PUB
  ${CMAKE_CURRENT_SOURCE_DIR}/include
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

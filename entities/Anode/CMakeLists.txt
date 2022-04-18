set(TARGET_NAME Anode)

find_package(vfs REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(ENTITY_DESCRIPTION Diode${TARGET_NAME}Description)
add_library(${ENTITY_DESCRIPTION} INTERFACE)
target_sources(${ENTITY_DESCRIPTION}
  INTERFACE include/AnodeDescription.h
)
target_include_directories(${ENTITY_DESCRIPTION}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(CLIENT_TARGET_NAME Diode${TARGET_NAME}Client)
add_subdirectory(client)

set(SERVER_TARGET_NAME Diode${TARGET_NAME}Server)
add_subdirectory(server)

set(SRCS
  src/AnodeCoordinator.cpp
  src/AnodeCoordinator.hpp
  src/main.cpp
)

set(LIBS_PRIV
  DiodeConfigurationManager
  DiodeRunner
  DiodeThreading
  DiodeAnodeServer
  DiodeTcpReceiver
  DiodeCathodeClient
  ${vfs_CLIENT_LIB}
)

set(LIBS_PUB
)

set(DIRS_PRIV
  ${CMAKE_CURRENT_SOURCE_DIR}/src
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

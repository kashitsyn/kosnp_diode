set(TARGET_NAME Diode)

set(CMAKE_CXX_STANDARD 17)

set(SRCS
  src/DiodeCoordinator.cpp
  src/DiodeCoordinator.hpp
  src/main.cpp
)

set(LIBS_PRIV
  DiodeConfigurationManager
  DiodeServiceManager
  DiodeInterrupter
  DiodeRunner
  DiodeTcpReceiver
  DiodeTcpSender
)

set(LIBS_PUB
)

set(DIRS_PRIV
)

set(DIRS_PUB
)

set(DEFS_PRIV
  DIODE_APP_DIR="${DEMO_APP_DIR}/Diode"
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

install(TARGETS ${TARGET_NAME} DESTINATION bin)

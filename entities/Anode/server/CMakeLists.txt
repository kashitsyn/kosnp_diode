set(TARGET_NAME ${SERVER_TARGET_NAME})

set(CMAKE_CXX_STANDARD 17)

build_entity(Anode
  EDL_FILES include/Anode.edl
)

set(SRCS
  include/AnodeServer.hpp
  include/AnodeServerImplFactory.hpp
  src/AnodeServerImpl.cpp
  src/AnodeServerImpl.hpp
  ${EDL_FILES}
)

set(LIBS_PRIV
  DiodeBaseService
  DiodeThreading
)

set(LIBS_PUB
  DiodeService
  DiodeTcpReceiver
  DiodeConfigurationManager
  ${ENTITY_DESCRIPTION}
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

add_library(${TARGET_NAME} ${SRCS})

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

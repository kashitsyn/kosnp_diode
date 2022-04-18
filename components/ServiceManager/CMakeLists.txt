set(TARGET_NAME DiodeServiceManager)

set(CMAKE_CXX_STANDARD 17)

set(SRCS
  include/ServiceManager.hpp
  include/ServiceManagerException.hpp
  include/ServiceManagerImplFactory.hpp
  src/ServiceManagerImpl.cpp
)

set(LIBS_PRIV
  DiodeBaseService
  DiodeThreading
)

set(LIBS_PUB
  DiodeException
  DiodeService
  DiodeTcpReceiver
  DiodeTcpSender
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

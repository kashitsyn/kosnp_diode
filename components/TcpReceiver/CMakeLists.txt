set(TARGET_NAME DiodeTcpReceiver)

set(CMAKE_CXX_STANDARD 17)

if(KOS)
  build_nk_component(TcpReceiver
    CDL_FILES include/TcpReceiver.cdl
    OUTPUT_FILES CDL_FILES
  )
endif()

set(SRCS
  include/TcpReceiver.hpp
  include/TcpReceiverException.hpp
  include/TcpReceiverImplFactory.hpp
  src/TcpReceiverImpl.cpp
  src/TcpReceiverImpl.hpp
)
if(KOS)
  list(APPEND SRCS
    include/TcpReceiverProxy.hpp
    include/TcpReceiverSkeleton.hpp
    ${CDL_FILES}
  )
endif()

set(LIBS_PRIV
  DiodeBaseService
)

set(LIBS_PUB
  DiodeDataStorage
  DiodeException
  DiodeService
  DiodeThreading
  DiodeConsumer
)
if(KOS)
  list(APPEND LIBS_PUB
    DiodeNkKosTransport
  )
endif()

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

set(TARGET_NAME DiodeInterrupter)

find_package(Threads)

set(CMAKE_CXX_STANDARD 17)

set(SRCS
  include/Interrupter.hpp
  include/InterrupterException.hpp
  include/InterrupterImplFactory.hpp
  src/InterrupterImpl.cpp
  src/InterrupterImpl.hpp
)

set(LIBS_PRIV
  Threads::Threads
)

set(LIBS_PUB
  DiodeException
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

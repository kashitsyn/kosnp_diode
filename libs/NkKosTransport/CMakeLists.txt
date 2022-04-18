set(TARGET_NAME DiodeNkKosTransport)

set(CMAKE_CXX_STANDARD 17)

set(SRCS
  include/NkKosTransport.hpp
)

set(LIBS_PRIV
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

set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

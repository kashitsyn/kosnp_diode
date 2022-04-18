project(env)

set(TARGET_NAME Env)

set(CMAKE_CXX_STANDARD 17)

build_entity(${TARGET_NAME}
  EDL_FILES "Env: kl.Env"
)

set(SRCS
  src/env.cpp
  ${EDL_FILES}
)

set(LIBS_PRIV
  ${env_SERVER_LIB}
)

set(LIBS_PUB
)

set(DIRS_PRIV
  ${CMAKE_CURRENT_BINARY_DIR}/src
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

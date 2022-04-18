set(TARGET_NAME DiodeService)

set(CMAKE_CXX_STANDARD 17)

if(KOS)
  build_nk_interface(
    IDL_FILES include/Service.idl
    OUTPUT_FILES IDL_FILES
  )
endif()

set(SRCS
  include/Service.hpp
)
if(KOS)
  list(APPEND SRCS
    include/ServiceProxy.hpp
    include/ServiceSkeleton.hpp
    src/ServiceProxy.cpp
    src/ServiceSkeleton.cpp
    ${IDL_FILES}
  )
endif()

set(LIBS_PRIV
)

set(LIBS_PUB
)
if(KOS)
  list(APPEND LIBS_PUB
    DiodeException
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

set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

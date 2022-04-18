set(TARGET_NAME DiodeConfigurationManager)

set(CMAKE_CXX_STANDARD 17)

if(KOS)
  build_nk_component(ConfigurationManager
    CDL_FILES include/ConfigurationManager.cdl
    OUTPUT_FILES CDL_FILES
  )
endif()

set(SRCS
  include/ConfigurationManager.hpp
  include/ConfigurationManagerException.hpp
  include/ConfigurationManagerImplFactory.hpp
  src/ConfigurationManagerImpl.cpp
  src/ConfigurationManagerImpl.hpp
)
if(KOS)
  list(APPEND SRCS
    include/ConfigurationManagerProxy.hpp
    include/ConfigurationManagerSkeleton.hpp
    ${CDL_FILES}
  )
endif()

set(LIBS_PRIV
)

set(LIBS_PUB
  DiodeException
  DiodeDataStorage
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

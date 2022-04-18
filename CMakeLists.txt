cmake_minimum_required(VERSION 3.16.3)
project(diode)

#
# Include CMake modules.
#

if(KOS)
  include(platform)
  initialize_platform()

  include(platform/nk)
  
  include(platform/install)
endif()

#
# Component selection options.
#

if(KOS)
  option(DEMO_USE_PRODUCTION_KSS_POLICIES "Use production KSS policies" OFF)
endif()

#
# QEMU options.
#

if(KOS)
  set(DEMO_QEMU_FLAGS "" CACHE STRING
    "Additional flags for QEMU"
  )
endif()

#
# Add subdirectories.
#

add_subdirectory(components)
add_subdirectory(dto)
add_subdirectory(interfaces)
add_subdirectory(libs)

if(KOS)
  add_subdirectory(entities)
  add_subdirectory(images)
else()
  add_subdirectory(app)
endif()

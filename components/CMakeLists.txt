if(KOS)
  include(platform/nk)
endif()

add_subdirectory(ServiceManager)
add_subdirectory(ConfigurationManager)
add_subdirectory(TcpSender)
add_subdirectory(TcpReceiver)

if(NOT KOS)
  add_subdirectory(Interrupter)
endif()

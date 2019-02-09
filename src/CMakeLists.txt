# library
#set(LIBRARY_NAME "telnet_protocol_1" CACHE INTERNAL "library name")

#add_library(${LIBRARY_NAME} telnet.cpp)

#target_include_directories(${LIBRARY_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)

#if(UNIX)
#    target_compile_options(${LIBRARY_NAME} PRIVATE -Werror)
#endif()
#target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_17)


# virtual network terminal server

set(SERVER_NVT "server_nvt" CACHE INTERNAL "server nvt")

add_executable(${SERVER_NVT} nvtd.cpp)

# windows features
if(MSVC)
    target_compile_options(${SERVER_NVT} PUBLIC "/MT$<$<CONFIG:Debug>:d>") #cl : Command line warning D9025 : overriding '/MDd' with '/MTd'
    target_link_libraries(${SERVER_NVT} PUBLIC Ws2_32)
endif()


# virtual network terminal client

set(CLIENT_NVT "client_nvt" CACHE INTERNAL "client nvt")

add_executable(${CLIENT_NVT} nvtc.cpp)

# windows features
if(MSVC)
    target_compile_options(${CLIENT_NVT} PUBLIC "/MT$<$<CONFIG:Debug>:d>")
    target_link_libraries(${CLIENT_NVT} PUBLIC Ws2_32)
endif()

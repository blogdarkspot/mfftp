# virtual network terminal server

set(SERVER_NVT "server_nvt" CACHE INTERNAL "server nvt")

add_executable(${SERVER_NVT} nvtd.cpp)

# windows features
if(MSVC)
    target_compile_options(${SERVER_NVT} PUBLIC "/MT$<$<CONFIG:Debug>:d>") #cl : Command line warning D9025 : overriding '/MDd' with '/MTd'
    target_link_libraries(${SERVER_NVT} PUBLIC Ws2_32)
    target_compile_features(${SERVER_NVT} PRIVATE cxx_std_17)
endif()


# virtual network terminal client

set(CLIENT_NVT "client_nvt" CACHE INTERNAL "client nvt")

add_executable(${CLIENT_NVT} nvtc.cpp)

# windows features
if(MSVC)
    target_compile_options(${CLIENT_NVT} PUBLIC "/MT$<$<CONFIG:Debug>:d>")
    target_link_libraries(${CLIENT_NVT} PUBLIC Ws2_32)
    target_compile_features(${CLIENT_NVT} PRIVATE cxx_std_17)
endif()

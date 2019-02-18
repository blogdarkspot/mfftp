# virtual network terminal server test
cmake_minimum_required(VERSION 3.12)
project(samples VERSION 1.0.0  DESCRIPTION "Samples to prove some concepts" LANGUAGES CXX)
if(MSVC)
    add_executable(server_nvt) 
    target_sources(server_nvt PRIVATE nvtd.cpp)
    target_compile_options(server_nvt PRIVATE "/MT$<$<CONFIG:Debug>:d>") #cl : Command line warning D9025 : overriding '/MDd' with '/MTd'
    target_link_libraries(server_nvt PRIVATE Ws2_32)
    target_compile_features(server_nvt PRIVATE cxx_std_17)

# virtual network terminal client tet
    add_executable(client_nvt)

# windows features
    target_sources(client_nvt PRIVATE nvtc.cpp)
    target_compile_options(client_nvt PRIVATE "/MT$<$<CONFIG:Debug>:d>")
    target_link_libraries(client_nvt PRIVATE Ws2_32)
    target_compile_features(client_nvt PRIVATE cxx_std_17)
endif()

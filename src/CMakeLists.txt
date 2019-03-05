#library commands
cmake_minimum_required(VERSION 3.12)

project(FTPLib VERSION 1.0.0 DESCRIPTION "Internal FTP Library Protocol" LANGUAGES CXX)

add_library(ftpMachinesOBJ OBJECT)
target_sources(ftpMachinesOBJ PRIVATE machines/machine.cpp machines/response_machines.cpp)
target_compile_features(ftpMachinesOBJ PUBLIC cxx_std_17)
target_include_directories(ftpMachinesOBJ PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_library(ftpLib)
target_include_directories(ftpLib INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ftpLib PUBLIC ftpMachinesOBJ)

add_library(FTP::Basic ALIAS ftpLib)

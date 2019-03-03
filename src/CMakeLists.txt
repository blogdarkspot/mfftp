#library commands
cmake_minimum_required(VERSION 3.12)

project(FTPLib VERSION 1.0.0 DESCRIPTION "Internal FTP Library Protocol" LANGUAGES CXX)

add_library(ftpCommandsOBJ OBJECT)
target_sources(ftpCommandsOBJ PRIVATE implftp.cpp)
target_compile_features(ftpCommandsOBJ PUBLIC cxx_std_17)
target_link_libraries(ftpCommandsOBJ PUBLIC stdc++fs)

add_library(ftpMachinesOBJ OBJECT)
target_sources(ftpMachinesOBJ PRIVATE machines/machine.cpp)
target_compile_features(ftpMachinesOBJ PUBLIC cxx_std_17)
target_include_directories(ftpMachinesOBJ PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_library(ftpLib)
target_include_directories(ftpLib INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ftpLib PUBLIC ftpCommandsOBJ ftpMachinesOBJ)

add_library(FTP::Basic ALIAS ftpLib)

#library commands
cmake_minimum_required(VERSION 3.12)

project(FTPLib VERSION 1.0.0 DESCRIPTION "Internal FTP Library Protocol" LANGUAGES CXX)

add_library(ftpCommandsOBJ OBJECT)
target_sources(ftpCommandsOBJ PRIVATE implftp.cpp)
if(MSVC)
    target_compile_options(ftpCommandsOBJ PUBLIC "/MT$<$<CONFIG:Debug>:d>")
endif()
target_compile_features(ftpCommandsOBJ PUBLIC cxx_std_17)
target_link_libraries(ftpCommandsOBJ PUBLIC stdc++fs)


if(MSVC)
add_library(ftpSession OBJECT)
target_sources(ftpSession PRIVATE session.cpp)
    target_compile_options(ftpSession PUBLIC "/MT$<$<CONFIG:Debug>:d>")
target_compile_features(ftpSession PUBLIC cxx_std_17)
endif()

add_library(ftpLib)
target_include_directories(ftpLib INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ftpLib PUBLIC ftpCommandsOBJ)
if(MSVC)
    target_link_libraries(ftpLib PUBLIC ftpSession)
endif()

add_library(FTP::Basic ALIAS ftpLib)
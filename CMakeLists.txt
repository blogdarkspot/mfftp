cmake_minimum_required(VERSION 3.12)

project(telnet VERSION 1.0.0 LANGUAGES CXX)

option(PACKAGE_TESTS "build the tests" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extern/catch2/contrib")

add_subdirectory(extern)

add_subdirectory(src)

if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

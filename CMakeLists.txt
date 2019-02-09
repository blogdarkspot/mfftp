cmake_minimum_required(VERSION 3.10)

project(telnet VERSION 1.0.0 LANGUAGES CXX)



add_subdirectory(src)

option(PACKAGE_TESTS "build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()



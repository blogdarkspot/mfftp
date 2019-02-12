add_subdirectory("${CMAKE_SOURCE_DIR}/extern/catch2" "extern/catch2")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extern/catch2/contrib")

set(TEST_COMMAND "test_commands" CACHE INTERNAL "tests to command")
add_executable(${TEST_COMMAND} testscmd.cpp)

if(MSVC)
    target_include_directories( ${TEST_COMMAND}
        PUBLIC
         ${CMAKE_SOURCE_DIR}/src
    )
    target_compile_options(${TEST_COMMAND} PUBLIC "/MT$<$<CONFIG:Debug>:d>")
    target_link_libraries(${TEST_COMMAND} ${LIBRARY_COMMAND} Catch2::Catch2)
    target_compile_features(${TEST_COMMAND} PUBLIC cxx_std_17)
endif()




include(CTest)
include(Catch)

catch_discover_tests(${TEST_COMMAND})
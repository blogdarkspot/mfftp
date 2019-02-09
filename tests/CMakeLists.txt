add_subdirectory("${CMAKE_SOURCE_DIR}/extern/catch2" "extern/catch2")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extern/catch2/contrib")

add_executable(tests_c test.cpp)

if(MSVC)
    target_compile_options(tests_c PUBLIC "/MT$<$<CONFIG:Debug>:d>")
    target_link_libraries(tests_c Catch2::Catch2)
    target_compile_features(tests_c PUBLIC cxx_std_17)
endif()

include(CTest)
include(Catch)

catch_discover_tests(tests_c)
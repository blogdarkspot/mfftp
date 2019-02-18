
message( STATUS "$ teste file ${CMAKE_MODULE_PATH}")
set(TEST_COMMAND "test_commands" CACHE INTERNAL "tests to command")

add_executable(UnitTest)

if(MSVC)
    target_sources(UnitTest PRIVATE tests_main.cpp tests_session.cpp tests_ImplFTP.cpp)
    target_compile_options(UnitTest PRIVATE "/MT$<$<CONFIG:Debug>:d>")
    target_link_libraries(UnitTest PRIVATE FTP::Basic Catch2::Catch2)
endif()

include(CTest)
include(Catch)

catch_discover_tests(UnitTest)
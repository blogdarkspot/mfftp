
message( STATUS "$ teste file ${CMAKE_MODULE_PATH}")

add_executable(UnitTest)
target_sources(UnitTest PRIVATE tests_main.cpp tests_ImplFTP.cpp)
target_link_libraries(UnitTest PRIVATE FTP::Basic Catch2::Catch2)

if(MSVC)
    target_sources(tests_session.cpp)
    target_compile_options(UnitTest PRIVATE "/MT$<$<CONFIG:Debug>:d>")
endif()

include(CTest)
include(Catch)

catch_discover_tests(UnitTest)
add_executable(UnitTest)
target_sources(UnitTest PRIVATE tests_main.cpp machine_test.cpp)
target_link_libraries(UnitTest PRIVATE FTP::Basic Catch2::Catch2)

include(CTest)
include(Catch)

catch_discover_tests(UnitTest)

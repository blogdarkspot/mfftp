set ( BOOST_VERSION 1.69.0 )

set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME ON)

find_package(Boost ${BOOST_VERSION} REQUIRED COMPONENTS filesystem)

if( Boost_FOUND )
    set_target_properties(Boost::filesystem PROPERTIES IMPORTED_GLOBAL TRUE)
endif()
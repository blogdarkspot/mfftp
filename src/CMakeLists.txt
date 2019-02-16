#library commands
if(MSVC)
    set(LIBRARY_COMMAND "cmd_windows" CACHE INTERNAL "library with commands avaliable")
    add_library(${LIBRARY_COMMAND} implcmd.cpp implftp.cpp session.cpp)
    target_include_directories(${LIBRARY_COMMAND} 
        PUBLIC 
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_SOURCE_DIR}/src
    )
    target_compile_options(${LIBRARY_COMMAND} PUBLIC "/MT$<$<CONFIG:Debug>:d>")
    target_compile_features(${LIBRARY_COMMAND} PUBLIC cxx_std_17)
endif()

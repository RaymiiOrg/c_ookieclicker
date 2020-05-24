cmake_minimum_required(VERSION 3.16)
project(c_ookiecliker)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )

set(GOOGLETEST_VERSION 3.14)
add_subdirectory(lib/googletest)

find_package(Boost REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    message("-- Boost found: ${Boost_VERSION_STRING}")
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME ON)
else()
    message(FATAL_ERROR "Boost not found!")
endif()
#
#SET(CMAKE_EXE_LINKER_FLAGS "-static")
#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#SET(BUILD_SHARED_LIBS OFF)

include_directories(src)
add_subdirectory(src)





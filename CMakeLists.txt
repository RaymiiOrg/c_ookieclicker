cmake_minimum_required(VERSION 3.16)
project(c_ookiecliker)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )

set(GOOGLETEST_VERSION 3.14)
add_subdirectory(lib/googletest)


include_directories(src)
add_subdirectory(src)





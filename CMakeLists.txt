cmake_minimum_required(VERSION 3.15)
project(c_ookiecliker VERSION 1.0.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
    message(STATUS "CMake generator is Visual Studio. Using Windows build flags")
    add_definitions(-DNOMINMAX -D_WIN32_WINNT=0x0A00 -DLANG_CXX17 -DCOMPILER_MSVC -D__VERSION__=\"MSVC\")
    add_definitions(-DWIN32 -DOS_WIN -D_MBCS -DWIN64 -DWIN32_LEAN_AND_MEAN -DNOGDI -DPLATFORM_WINDOWS)
    add_definitions(/bigobj /nologo /EHsc /GF /FC /MP /Gm-)
    # Suppress warnings to reduce build log size.
    add_definitions(/wd4267 /wd4244 /wd4800 /wd4503 /wd4554 /wd4996 /wd4348 /wd4018)
    add_definitions(/wd4099 /wd4146 /wd4267 /wd4305 /wd4307)
    add_definitions(/wd4715 /wd4722 /wd4723 /wd4838 /wd4309 /wd4334)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()


if (STATIC_COMPILE STREQUAL "yes")
    # Fix segfault when statically compiling.
    # https://stackoverflow.com/questions/35116327/when-g-static-link-pthread-cause-segmentation-fault-why
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -lrt -pthread -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
    SET(CMAKE_EXE_LINKER_FLAGS "-static")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    SET(BUILD_SHARED_LIBS OFF)
endif()

message(STATUS "Cmake Generator: ${CMAKE_GENERATOR}")

# For github actions, use boost from their non standard directory
if(DEFINED ENV{BOOST_ROOT_1_72_0})
    SET (BOOST_ROOT "$ENV{BOOST_ROOT_1_72_0}")
    message(STATUS "Boost root from github found, using that.")
endif()

find_package(Boost REQUIRED COMPONENTS)
if(BOOST_FOUND)
    include_directories(${BOOST_INCLUDE_DIR})
    message("-- Boost found: ${BOOST_VERSION_STRING}")
    set(BOOST_USE_STATIC_LIBS ON)
    set(BOOST_USE_MULTITHREADED ON)
    set(BOOST_USE_STATIC_RUNTIME ON)
else()
    message(FATAL_ERROR "Boost not found!")
endif()

if (NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
    message(STATUS "CMake generator is NOT Visual Studio. Using regular build flags")

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -U_FORTIFY_SOURCE -ggdb")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -Wall -U_FORTIFY_SOURCE -ggdb")
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 ")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -DNDEBUG")
    endif()
endif()

if (BUILD_TESTS STREQUAL "yes")
    set(GOOGLETEST_VERSION 3.14)
    add_subdirectory(lib/googletest)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CXX_FILESYSTEM_LIBRARIES)
elseif (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
   set(CXX_FILESYSTEM_LIBRARIES stdc++fs)
else()
    set(CXX_FILESYSTEM_LIBRARIES)
endif()


include_directories(src)
add_subdirectory(src)

find_package(Git)
if (GIT_FOUND)
    execute_process(COMMAND
            "${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=40 --dirty
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE GIT_SHA
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

    set(PACKAGE_GITSHA "\"${GIT_SHA}\"")
endif()

set(PACKAGE ${PROJECT_NAME})
set(PACKAGE_NAME string(TOLOWER ${PROJECT_NAME}))
set(PACKAGE_VERSION ${PROJECT_VERSION})
set(PACKAGE_STRING ${PACKAGE_NAME}-${PACKAGE_VERSION})
set(PACKAGE_TARNAME ${PACKAGE_STRING}.tar.gz)
set(PACKAGE_URL "https://raymii.org")

configure_file(src/config.hpp.in src/config.hpp)

install(TARGETS cookieclicker_linux DESTINATION bin)


message(STATUS "C++ compiler flags  : ${CMAKE_CXX_FLAGS}")
message(STATUS "C compiler flags    : ${CMAKE_C_FLAGS}")
message(STATUS "Linker flags        : ${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_STATIC_LINKER_FLAGS}")

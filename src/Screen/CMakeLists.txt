add_subdirectory(src)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(tst)
endif()
add_subdirectory(src)
if (BUILD_TESTS STREQUAL "yes")
    add_subdirectory(tst)
endif()
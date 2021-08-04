set(LIBRARY Screen)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_library(${LIBRARY} STATIC ${SOURCES})

target_include_directories(${LIBRARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY} PUBLIC cookieclicker Commands)

if(Boost_FOUND)
    target_link_libraries (${LIBRARY} ${Boost_LIBRARIES})
elseif(USEBOOST_MPP)
    message(FATAL_ERROR "Boost not found, but specified as USEBOOST_MPP=$USEBOOST_MPP!")
endif()

MESSAGE("-- Loaded ${LIBRARY}")
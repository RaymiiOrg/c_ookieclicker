set(LIBRARY cookieclicker)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_library(${LIBRARY} STATIC ${SOURCES})

target_link_libraries(${LIBRARY} PUBLIC
        ${CURSES_LIBRARY}
        Commands
        Wallet
        Store
        Achievements
        Screen
        )
target_link_libraries(${LIBRARY} PUBLIC Threads::Threads)
target_link_libraries(${LIBRARY} PUBLIC ${CXX_FILESYSTEM_LIBRARIES})

target_include_directories(${LIBRARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${LIBRARY}_linux ${SOURCES})
target_link_libraries(${LIBRARY}_linux PUBLIC
        ${CURSES_LIBRARY}
        Commands
        Wallet
        Achievements
        Screen
        Store)
target_link_libraries(${LIBRARY}_linux PUBLIC Threads::Threads)
target_link_libraries(${LIBRARY} PUBLIC ${CXX_FILESYSTEM_LIBRARIES})

target_include_directories(${LIBRARY}_linux PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(Boost_FOUND)
    target_link_libraries (${LIBRARY} ${Boost_LIBRARIES})
    target_link_libraries (${LIBRARY}_linux ${Boost_LIBRARIES})
elseif(USEBOOST_MPP)
    message(FATAL_ERROR "Boost not found, but specified as USEBOOST_MPP=$USEBOOST_MPP!")
endif()

MESSAGE("-- Loaded ${LIBRARY}")
MESSAGE("-- Executable: ${LIBRARY}_linux")

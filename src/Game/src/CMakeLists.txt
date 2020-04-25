set(LIBRARY Game)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_library(${LIBRARY} STATIC ${SOURCES})

target_link_libraries(${LIBRARY} PUBLIC
        ${CURSES_LIBRARY}
        Commands
        Wallet
        gtest)

target_include_directories(${LIBRARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${LIBRARY}.exe ${SOURCES})
target_link_libraries(${LIBRARY}.exe PUBLIC
        ${CURSES_LIBRARY}
        Commands
        Wallet)
target_include_directories(${LIBRARY}.exe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

MESSAGE("Loaded ${LIBRARY}")
MESSAGE("Executable: ${LIBRARY}.exe")
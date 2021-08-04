configure_file (
        "${CMAKE_CURRENT_SOURCE_DIR}/cmakeConfig.h.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmakeConfig.h"
)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/")

add_subdirectory(Wallet)
add_subdirectory(Store)
add_subdirectory(Commands)
add_subdirectory(Achievements)
add_subdirectory(Screen)
add_subdirectory(Game)

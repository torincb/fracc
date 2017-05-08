cmake_minimum_required(VERSION 3.7)
project(FRACC)
set(FRACC_VERSION_MAJOR 0)
set(FRACC_VERSION_MINOR 1)

configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )
include_directories("${PROJECT_BINARY_DIR}")

# Find SDL2 (using tcbrindle's scripts because CMake is outdated, grr)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/sdl2")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# add subdirs (will create list of source files in SRCS)
add_subdirectory("src")

add_executable(fracc ${SRCS})

# link libs
target_link_libraries(fracc ${SDL2_LIBRARY})

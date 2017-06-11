cmake_minimum_required(VERSION 3.7)
project(FRACC CXX)
set(FRACC_VERSION_MAJOR 0)
set(FRACC_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")
set(CMAKE_CXX_STANDARD 11)

configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )
include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Find SDL2 (using tcbrindle's scripts because CMake is outdated, grr)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/sdl2")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# set(CMAKE_AUTOMOC ON)
# find_package(Qt5Widgets REQUIRED)

# add subdirs (will create list of source files in SRCS)
add_subdirectory("src")

add_executable(fracc ${SRCS})

# link libs
target_link_libraries(fracc ${SDL2_LIBRARY})
# target_link_libraries(fracc ${SDL2_LIBRARY} Qt5::Widgets)

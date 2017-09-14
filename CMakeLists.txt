cmake_minimum_required(VERSION 3.7)
project(FRACC CXX)
set(FRACC_VERSION_MAJOR 0)
set(FRACC_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")
set(CMAKE_CXX_STANDARD 14)

include_directories("src")

# add subdirs (will create list of source files in SRCS)
add_subdirectory("src/cli")

add_executable(fracc ${SRCS})
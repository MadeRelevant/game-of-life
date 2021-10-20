cmake_minimum_required(VERSION 3.20)
project(gameoflife)

set(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_FLAGS -pthread)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(include)


add_executable(gameoflife main.cpp Grid.cpp Grid.h World.cpp World.h)
target_link_libraries(gameoflife ${CURSES_LIBRARY})

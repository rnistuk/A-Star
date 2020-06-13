cmake_minimum_required(VERSION 3.15)
project(A-Star)

set(CMAKE_CXX_STANDARD 17)

INCLUDE(FindPkgConfig)

# SDL2 - install SDL2 with 'brew install sdl2'
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDEDIR})
link_directories(${SDL2_LIBRARY_DIRS})

# Add the demo subdirectory
add_subdirectory(a-star)

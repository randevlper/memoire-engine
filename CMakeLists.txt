cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(goldgame)

add_subdirectory(thirdparty/SDL2)
add_subdirectory(thirdparty/Box2D)

SET(BUILD_TESTING OFF CACHE BOOL "Enable testing with ctest.")
add_subdirectory(thirdparty/entt)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE thirdparty/stb)

add_subdirectory(game)
#add_subdirectory(engine)
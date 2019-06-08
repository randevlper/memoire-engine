cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(goldgame)

SET(SDL_SHARED OFF CACHE BOOL "Dont use SDL2 shared lib")
add_subdirectory(thirdparty/SDL2)
add_subdirectory(thirdparty/Box2D)

SET(BUILD_SHARED_LIBS OFF CACHE BOOL "Disable Glm shared libs")
SET(GLM_TEST_ENABLE_CXX_14 ON CACHE BOOL "Enable C++ 14")
SET(GLM_TEST_ENABLE OFF CACHE BOOL "Disable test projects")
add_subdirectory(thirdparty/glm)

SET(BUILD_TESTING OFF CACHE BOOL "Enable testing with ctest.")
add_subdirectory(thirdparty/entt)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE thirdparty/stb)

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(test)
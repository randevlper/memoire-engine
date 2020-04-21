cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(memoire-engine)

SET(SDL_SHARED OFF CACHE BOOL "Dont use SDL2 shared lib")
add_subdirectory(thirdparty/SDL-mirror)
set_target_properties(SDL2-static PROPERTIES FOLDER "Thirdparty")
set_target_properties(SDL2main PROPERTIES FOLDER "Thirdparty")

add_subdirectory(thirdparty/bgfx.cmake)

SET(BUILD_SHARED_LIBS OFF CACHE BOOL "Disable Glm shared libs")
SET(GLM_TEST_ENABLE_CXX_14 ON CACHE BOOL "Enable C++ 14")
SET(GLM_TEST_ENABLE OFF CACHE BOOL "Disable test projects")
add_subdirectory(thirdparty/glm)
#set_target_properties(glm PROPERTIES FOLDER "Thirdparty")
#Interface

SET(BUILD_TESTING OFF CACHE BOOL "Enable testing with ctest.")
add_subdirectory(thirdparty/entt)
#set_target_properties(EnTT PROPERTIES FOLDER "Thirdparty")
#Interface

SET(ZLIB_ENABLE_TESTS  OFF CACHE BOOL "Dont build Zlib tests")
add_subdirectory(thirdparty/zlib)
set_target_properties(zlib PROPERTIES FOLDER "Thirdparty")
set_target_properties(zlibstatic PROPERTIES FOLDER "Thirdparty")
set_target_properties(minigzip PROPERTIES FOLDER "Thirdparty/Tests")
set_target_properties(example PROPERTIES FOLDER "Thirdparty/Tests")

add_subdirectory(thirdparty/Box2D-cmake)
set_target_properties(Box2D-cmake PROPERTIES FOLDER "Thirdparty")

add_subdirectory(thirdparty/freetype2)
set_target_properties(freetype PROPERTIES FOLDER "Thirdparty")

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE thirdparty/stb)
#set_target_properties(stb PROPERTIES FOLDER "Thirdparty")
#Interface
add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE thirdparty/miniaudio)

add_subdirectory(engine)
add_subdirectory(engine-tests)
add_subdirectory(game)
add_subdirectory(librarian)
add_subdirectory(test)
add_subdirectory(test_bgfx)
set_target_properties(engine PROPERTIES FOLDER "Engine")
set_target_properties(engine-tests PROPERTIES FOLDER "Engine")
set_target_properties(game PROPERTIES FOLDER "Games")
set_target_properties(librarian PROPERTIES FOLDER "Games")
set_target_properties(test PROPERTIES FOLDER "Engine")
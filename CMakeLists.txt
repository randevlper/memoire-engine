cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
include(ExternalProject)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(memoire-engine)

SET(SDL_SHARED OFF CACHE BOOL "Dont use SDL2 shared lib")
add_subdirectory(thirdparty/SDL)
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
set_target_properties(entt_aob PROPERTIES FOLDER "Thirdparty")
#Interface

SET(ZLIB_ENABLE_TESTS  OFF CACHE BOOL "Dont build Zlib tests")
add_subdirectory(thirdparty/zlib)
set_target_properties(zlib PROPERTIES FOLDER "Thirdparty")
set_target_properties(zlibstatic PROPERTIES FOLDER "Thirdparty")
set_target_properties(minigzip PROPERTIES FOLDER "Thirdparty/Tests")
set_target_properties(example PROPERTIES FOLDER "Thirdparty/Tests")

SET(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "Dont build unit tests")
SET(BOX2D_BUILD_TESTBED OFF CACHE BOOL "Dont build testbed")
add_subdirectory(thirdparty/box2d)
set_target_properties(box2d PROPERTIES FOLDER "Thirdparty")

add_subdirectory(thirdparty/freetype2)
set_target_properties(freetype PROPERTIES FOLDER "Thirdparty")

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE thirdparty/stb)
#set_target_properties(stb PROPERTIES FOLDER "Thirdparty")
#Interface
add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE thirdparty/miniaudio)

#\thirdparty\bgfx.cmake\bgfx\examples\common\imgui
file(GLOB_RECURSE IMGUI_SOURCES
    thirdparty/bgfx.cmake/bgfx/examples/common/imgui/*.h
	thirdparty/bgfx.cmake/bgfx/examples/common/imgui/*.cpp
)
add_library(bgfx_imgui STATIC ${IMGUI_SOURCES})
target_link_libraries(bgfx_imgui bgfx dear-imgui)
target_include_directories(bgfx_imgui PUBLIC thirdparty/bgfx.cmake/bgfx/examples)
set_target_properties(bgfx_imgui PROPERTIES FOLDER "Thirdparty")

#Add Lua
include(FetchContent)
FetchContent_Declare(
  LuaLib
  URL https://www.lua.org/ftp/lua-5.4.1.tar.gz
)
FetchContent_Populate(LuaLib)
file(COPY "${CMAKE_SOURCE_DIR}/build/_deps/lualib-src/" 
     DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lua/")
#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lua/CMakeLists.txt" 
#     DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lua/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lua/")
set_target_properties(LuaLib PROPERTIES FOLDER "Thirdparty")

#JSON CPP
# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(thirdparty/json)

add_subdirectory(engine)
add_subdirectory(engine-tests)
set_target_properties(engine PROPERTIES FOLDER "Engine")
set_target_properties(engine-tests PROPERTIES FOLDER "Engine")

add_subdirectory(game)
add_subdirectory(librarian)
set_target_properties(game PROPERTIES FOLDER "Games")
set_target_properties(librarian PROPERTIES FOLDER "Games")
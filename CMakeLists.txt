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

#\thirdparty\bgfx.cmake\bgfx\examples\common\imgui
file(GLOB_RECURSE IMGUI_SOURCES
    thirdparty/bgfx.cmake/bgfx/examples/common/imgui/*.h
	thirdparty/bgfx.cmake/bgfx/examples/common/imgui/*.cpp
)
add_library(bgfx_imgui STATIC ${IMGUI_SOURCES})
target_link_libraries(bgfx_imgui bgfx dear-imgui)
target_include_directories(bgfx_imgui PUBLIC thirdparty/bgfx.cmake/bgfx/examples)

#Add Lua
set (LUA_RUNTIME_SOURCES
"thirdparty/lua/lapi.c"
"thirdparty/lua/lapi.h"
"thirdparty/lua/lauxlib.c"
"thirdparty/lua/lauxlib.h"
"thirdparty/lua/lbaselib.c"
#"thirdparty/lua/lbitlib.c"
"thirdparty/lua/lcode.c"
"thirdparty/lua/lcode.h"
"thirdparty/lua/lcorolib.c"
"thirdparty/lua/lctype.c"
"thirdparty/lua/lctype.h"
"thirdparty/lua/ldblib.c"
"thirdparty/lua/ldebug.c"
"thirdparty/lua/ldebug.h"
"thirdparty/lua/ldo.c"
"thirdparty/lua/ldo.h"
"thirdparty/lua/ldump.c"
"thirdparty/lua/lfunc.c"
"thirdparty/lua/lfunc.h"
"thirdparty/lua/lgc.c"
"thirdparty/lua/lgc.h"
"thirdparty/lua/linit.c"
"thirdparty/lua/liolib.c"
"thirdparty/lua/ljumptab.h"
"thirdparty/lua/llex.c"
"thirdparty/lua/llex.h"
"thirdparty/lua/llimits.h"
"thirdparty/lua/lmathlib.c"
"thirdparty/lua/lmem.c"
"thirdparty/lua/lmem.h"
"thirdparty/lua/loadlib.c"
"thirdparty/lua/lobject.c"
"thirdparty/lua/lobject.h"
"thirdparty/lua/lopcodes.c"
"thirdparty/lua/lopcodes.h"
"thirdparty/lua/lopnames.h"
"thirdparty/lua/loslib.c"
"thirdparty/lua/lparser.c"
"thirdparty/lua/lparser.h"
"thirdparty/lua/lprefix.h"
"thirdparty/lua/lstate.c"
"thirdparty/lua/lstate.h"
"thirdparty/lua/lstring.c"
"thirdparty/lua/lstring.h"
"thirdparty/lua/lstrlib.c"
"thirdparty/lua/ltable.c"
"thirdparty/lua/ltable.h"
"thirdparty/lua/ltablib.c"
"thirdparty/lua/ltm.c"
"thirdparty/lua/ltm.h"
"thirdparty/lua/lua.c"
"thirdparty/lua/lua.h"
#"thirdparty/lua/lua.hpp"
#"thirdparty/lua/luac.c"
"thirdparty/lua/luaconf.h"
"thirdparty/lua/lualib.h"
"thirdparty/lua/lundump.c"
"thirdparty/lua/lundump.h"
"thirdparty/lua/lutf8lib.c"
"thirdparty/lua/lvm.c"
"thirdparty/lua/lvm.h"
"thirdparty/lua/lzio.c"
"thirdparty/lua/lzio.h"
#"thirdparty/lua/onelua.c"
)
add_library(LuaLib ${LUA_RUNTIME_SOURCES})
target_include_directories ( LuaLib PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/lua")


#JSON CPP
# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(thirdparty/json)

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
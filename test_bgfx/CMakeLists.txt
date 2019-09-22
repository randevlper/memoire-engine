cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(test_bgfx)

file(GLOB_RECURSE SOURCES
	src/*.h
	src/*.cpp
)

add_executable(test_bgfx ${SOURCES})

set_property(TARGET test_bgfx PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_bgfx")
target_link_libraries(test_bgfx SDL2-static stb EnTT bgfx glm)
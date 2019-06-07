cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(test)

file(GLOB SOURCES
	src/*.h
	src/*.cpp
)

add_executable(test ${SOURCES})

set_property(TARGET test PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")

target_link_libraries(test SDL2-static Box2D-cmake stb EnTT)
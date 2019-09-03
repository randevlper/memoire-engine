cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(game)

file(GLOB SOURCES
	src/*.h
	src/*.cpp
)

add_executable(game ${SOURCES})

set_property(TARGET game PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/game")

target_link_libraries(game SDL2-static stb EnTT engine glm)
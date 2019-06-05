cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(game)

add_executable(game
	main.cpp
)

set_property(TARGET game PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/game")

target_link_libraries(game SDL2-static Box2D-cmake stb EnTT)
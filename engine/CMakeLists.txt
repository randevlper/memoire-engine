cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(engine)

file(GLOB_RECURSE SOURCES
	Engine/*.h
	Engine/*.cpp
)

add_library(engine STATIC ${SOURCES})
target_include_directories(engine PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(engine SDL2-static stb EnTT glm zlibstatic bgfx Box2D-cmake freetype miniaudio)
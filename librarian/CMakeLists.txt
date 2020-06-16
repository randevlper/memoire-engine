cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(librarian)

file(GLOB_RECURSE SOURCES
	src/*.h
	src/*.cpp
)

add_executable(librarian ${SOURCES})
target_include_directories(librarian PUBLIC ${PROJECT_SOURCE_DIR}/src)
set_property(TARGET librarian PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/librarian")

target_link_libraries(librarian SDL2-static stb EnTT engine glm bgfx_imgui)
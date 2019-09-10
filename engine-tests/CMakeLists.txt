cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(engine-tests)

file(GLOB SOURCES
	src/*.cpp
)

add_executable(engine-tests ${SOURCES})

set_property(TARGET engine-tests PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/engine-tests")

target_link_libraries(engine-tests SDL2-static stb EnTT engine glm)
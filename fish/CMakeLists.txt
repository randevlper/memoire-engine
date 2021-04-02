cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(fish)

file(GLOB_RECURSE SOURCES
	src/*.h
	src/*.cpp
)

if(MSVC)
	add_compile_options(/MP4)				#Use multiple processors when building
	#add_compile_options(/W4 /wd4201 /WX)	#Warning level 4, all warnings are errors
else()
	#add_compile_options(-W -Wall -Werror) #All Warnings, all warnings are errors
endif()

add_executable(fish ${SOURCES})
target_include_directories(fish PUBLIC ${PROJECT_SOURCE_DIR}/src)
set_property(TARGET fish PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/fish")

target_link_libraries(fish SDL2-static stb EnTT engine glm bgfx_imgui LuaLib box2d)
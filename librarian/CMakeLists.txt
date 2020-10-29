cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(librarian)

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

add_executable(librarian ${SOURCES})
target_include_directories(librarian PUBLIC ${PROJECT_SOURCE_DIR}/src)
set_property(TARGET librarian PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/librarian")

target_link_libraries(librarian SDL2-static stb EnTT engine glm bgfx_imgui LuaLib)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(engine)

# file(GLOB_RECURSE SOURCES
# 	Engine/*.h
# 	Engine/*.cpp
# )

#should be able to use some kind of loop
file(GLOB_RECURSE SOURCES_CORE
 	Engine/Core/*.h
 	Engine/Core/*.cpp
)

file(GLOB_RECURSE SOURCES_ASSETMANAGEMENT
	Engine/AssetManagement/*.h
	Engine/AssetManagement/*.cpp
)

file(GLOB_RECURSE SOURCES_DATA
	Engine/Data/*.h
	Engine/Data/*.cpp
)

file(GLOB_RECURSE SOURCES_NODES
	Engine/Nodes/*.h
	Engine/Nodes/*.cpp
)

file(GLOB_RECURSE SOURCES_THIRDPARTY
	Engine/thirdparty/*.h
	Engine/thirdparty/*.cpp
)

file(GLOB_RECURSE SOURCES_TOOLS
	Engine/Tools/*.h
	Engine/Tools/*.cpp
)

file(GLOB_RECURSE SOURCES_UI
	Engine/UI/*.h
	Engine/UI/*.cpp
)

file(GLOB_RECURSE SOURCES_UTILITIES
	Engine/Utilities/*.h
	Engine/Utilities/*.cpp
)

file(GLOB_RECURSE SOURCES_IMGUI
	Engine/IMGUI/*.h
	Engine/IMGUI/*.cpp
)

file(GLOB_RECURSE SOURCES_PHYSICS2D
	Engine/Physics2D/*.h
	Engine/Physics2D/*.cpp
)

add_library(engine STATIC ${SOURCES_CORE} ${SOURCES_ASSETMANAGEMENT} ${SOURCES_DATA} ${SOURCES_NODES} ${SOURCES_THIRDPARTY} ${SOURCES_TOOLS} ${SOURCES_UI} ${SOURCES_UTILITIES} ${SOURCES_IMGUI} ${SOURCES_PHYSICS2D})

source_group("AssetManagement" FILES ${SOURCES_ASSETMANAGEMENT})
source_group("Core" FILES ${SOURCES_CORE})
source_group("Data" FILES ${SOURCES_DATA})
source_group("Nodes" FILES ${SOURCES_NODES})
source_group("Thirdparty" FILES ${SOURCES_THIRDPARTY})
source_group("Tools" FILES ${SOURCES_TOOLS})
source_group("UI" FILES ${SOURCES_UI})
source_group("Utilities" FILES ${SOURCES_UTILITIES})
source_group("IMGUI" FILES ${SOURCES_IMGUI})
source_group("Physics2D" FILES ${SOURCES_PHYSICS2D})

if(MSVC)
	add_compile_options(/MP4)				#Use multiple processors when building
	#add_compile_options(/W4 /wd4201 /WX)	#Warning level 4, all warnings are errors
else()
	#add_compile_options(-W -Wall -Werror) #All Warnings, all warnings are errors
endif()


target_include_directories(engine PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(engine SDL2-static stb EnTT glm zlibstatic box2d freetype miniaudio nlohmann_json::nlohmann_json)
target_link_libraries(engine bgfx_imgui LuaLib)
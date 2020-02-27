#include "ShaderLoader.h"

#include "Shader.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/Utilities/DebugMemory.h"

void ShaderLoader::init()
{

}

void ShaderLoader::destroy()
{

}

Asset* ShaderLoader::load(std::string path, std::string vars)
{
	Shader* shader = DBG_NEW Shader(FileUtility::loadProgram(path.c_str(), 
		vars.c_str()));
	return shader;
}

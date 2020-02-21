#include "AssetLoader.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/AssetManagement/Asset.h"

AssetLoader::AssetLoader(){}

AssetLoader::~AssetLoader(){}

void AssetLoader::init()
{
	Debug::Log("Unimplemented Loader Init");
}

void AssetLoader::destroy()
{
	Debug::Log("Unimplemented Loader Destroy");
}

Asset* AssetLoader::load(std::string path, std::string vars)
{
	Debug::Log("Unimplemented Loader Load");
	return nullptr;
}

#include "SpriteLoader.h"

#include <bgfx/bgfx.h>

#include "Engine/AssetManagement/Asset.h"
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/Core/FileUtility.h"


void SpriteLoader::init()
{
	_fileExtension = ".png";
}

void SpriteLoader::destroy()
{
}

Asset* SpriteLoader::load(std::string path, std::string vars)
{
	return FileUtility::loadTexture(path.c_str(), BGFX_TEXTURE_NONE | BGFX_SAMPLER_POINT, 0, NULL, NULL);
}
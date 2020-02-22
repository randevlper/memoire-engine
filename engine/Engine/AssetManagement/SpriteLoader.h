#pragma once
#include <string>
#include "Engine/AssetManagement/AssetLoader.h"
class Asset;


class SpriteLoader : public AssetLoader
{
public:
	SpriteLoader(){}
	~SpriteLoader(){}

	void init() override;
	void destroy() override;
	Asset* load(std::string path, std::string vars) override;

private:

};
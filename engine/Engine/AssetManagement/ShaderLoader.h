#pragma once
#include "AssetLoader.h"

class ShaderLoader : public AssetLoader
{
public:
	ShaderLoader() {};
	~ShaderLoader() {};

	void init() override;
	void destroy() override;
	Asset* load(std::string path, std::string vars) override;
	const std::string _fileExtension = ".bin";

private:

};
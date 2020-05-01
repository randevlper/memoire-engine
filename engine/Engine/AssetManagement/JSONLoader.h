#pragma once
#include "AssetLoader.h"

#include <string>
class Asset;

class JSONLoader : public AssetLoader
{
public:

	JSONLoader();
	~JSONLoader();

	void init() override;
	void destroy() override;
	Asset* load(std::string path, std::string vars) override;
	std::string _fileExtension = ".json";

private:


};
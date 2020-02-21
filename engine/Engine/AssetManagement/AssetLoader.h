#pragma once
#include <string>
class Asset;

class AssetLoader
{
public:

	AssetLoader();
	~AssetLoader();

	virtual void init();
	virtual void destroy();
	virtual Asset* load(std::string path, std::string vars);
	std::string _fileExtension;

private:
	

};
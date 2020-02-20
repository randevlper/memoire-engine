#pragma once
#include <string>

class AssetLoader
{
public:

	AssetLoader();
	~AssetLoader();

	virtual void init();
	virtual void destroy();
	virtual void* load(std::string path, std::string vars);
	std::string _fileExtension;

private:
	

};
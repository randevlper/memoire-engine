#pragma once
#include "AssetLoader.h"
class Font;

class FontLoader : public AssetLoader
{
public:
	FontLoader() {};
	~FontLoader() {};

	void init() override;
	void destroy() override;
	void* load(std::string path, std::string vars) override;
	const std::string _fileExtension = ".ttf";

private:

	static void* _FT_LIB;
};
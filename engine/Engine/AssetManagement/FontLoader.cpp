#include "FontLoader.h"

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Font.h"

void* FontLoader::_FT_LIB = nullptr;

void FontLoader::init()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	_FT_LIB = ft;
}

void FontLoader::destroy()
{
	FT_Done_FreeType((FT_Library)_FT_LIB);
}

Font* FontLoader::load(char* path, int fontSize)
{
	FT_Face face;
	if (FT_New_Face((FT_Library)_FT_LIB, path, 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
	else {
		std::cout << "LOG::FREETYPE: Loaded " << path << std::endl;
	}
	return new Font(face, fontSize);
}

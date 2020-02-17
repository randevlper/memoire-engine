#include "FontLoader.h"

#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


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
	return DBG_NEW Font(face, fontSize);
}

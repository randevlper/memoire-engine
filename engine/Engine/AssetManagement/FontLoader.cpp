#include "FontLoader.h"

#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"


#include <ft2build.h>
#include FT_FREETYPE_H

#include "Font.h"

void* FontLoader::_FT_LIB = nullptr;

void FontLoader::init()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		Debug::Log("ERROR::FREETYPE: Could not init FreeType Library");
	}

	_FT_LIB = ft;
}

void FontLoader::destroy()
{
	FT_Done_FreeType((FT_Library)_FT_LIB);
}

void* FontLoader::load(std::string path, std::string vars)
{
	FT_Face face;
	if (FT_New_Face((FT_Library)_FT_LIB, path.c_str(), 0, &face)) {
		Debug::Log("ERROR::FREETYPE: Failed to load font");
	}
	else {
		Debug::Log("LOG::FREETYPE: Loaded " + path);
	}
	return DBG_NEW Font(face, std::stoi(vars));
}

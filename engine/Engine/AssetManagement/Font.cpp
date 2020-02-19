#include "Font.h"

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Engine/Utilities/DebugMemory.h"

Font::Font(void* face, unsigned int fontSize)
{
	_ft_face = face;
	_fontHeight = fontSize;
	FT_Face FTface = (FT_Face)_ft_face;

	FT_Set_Pixel_Sizes(FTface, 0, _fontHeight);

	uint64_t flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_POINT;

	for (size_t c = 0; c < 128; c++)
	{
		if (FT_Load_Char(FTface, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		//else {
		//	std::cout << "LOG::FREETYTPE: Loaded " << (char)c << std::endl;
		//}

		bgfx::TextureHandle handle;
		bgfx::TextureFormat::Enum format = bgfx::TextureFormat::Enum::A8;

		switch (FTface->glyph->bitmap.pixel_mode)
		{
		case FT_PIXEL_MODE_MONO:
			format = bgfx::TextureFormat::Enum::ETC2A1;
			break;
		case FT_PIXEL_MODE_GRAY:
			format = bgfx::TextureFormat::Enum::A8;
			break;
		case FT_PIXEL_MODE_LCD:
			format = bgfx::TextureFormat::Enum::RGB8;
			break;
		case FT_PIXEL_MODE_LCD_V:
			format = bgfx::TextureFormat::Enum::RGB8;
			break;
		case FT_PIXEL_MODE_BGRA:
			format = bgfx::TextureFormat::Enum::BGRA8;
			break;
		default:
			continue;
		}

		
		if (bgfx::isTextureValid(0, false, 1, format, flags)
			&& (FTface->glyph->bitmap.pitch * FTface->glyph->bitmap.rows > 0)) {

			handle = bgfx::createTexture2D(
				FTface->glyph->bitmap.width,
				FTface->glyph->bitmap.rows,
				0, 1, format,
				flags,
				bgfx::copy(
					FTface->glyph->bitmap.buffer,
					FTface->glyph->bitmap.pitch * FTface->glyph->bitmap.rows
				));

			if (bgfx::isValid(handle)) {
				Character character = {
					handle,
					glm::ivec2(FTface->glyph->bitmap.width, FTface->glyph->bitmap.rows),
					glm::ivec2(FTface->glyph->bitmap_left, FTface->glyph->bitmap_top),
					FTface->glyph->advance.x
				};
				characters.insert(std::pair<char, Character>(c, character));
			}
		}
		else {
			std::cout << "ERROR::FREETYTPE:FONT Failed to create Handle! |" << (char)c << std::endl;
		}
	}
	FT_Done_Face((FT_Face)_ft_face);
}

Font::~Font()
{
	for (size_t i = 0; i < characters.size(); i++)
	{
		if (bgfx::isValid(characters[i].Handle) && characters[i].Handle.idx != 0) {
			bgfx::destroy(characters[i].Handle);
		}
	}
}

Character Font::getCharacter(char c)
{
	std::map<char, Character>::iterator it = characters.find(c);
	if (it == characters.end())
	{
		std::cout << "Tim is not in the map!" << std::endl;
	}
	return it->second;
}

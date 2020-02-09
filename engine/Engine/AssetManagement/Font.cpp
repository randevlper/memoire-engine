#include "Font.h"

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

Font::Font(void* face, unsigned int fontSize)
{
	_ft_face = face;
	_fontHeight = fontSize;
	FT_Face FTface = (FT_Face)_ft_face;

	FT_Set_Pixel_Sizes(FTface, 0, 48);

	uint64_t flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE;

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
		bgfx::TextureFormat::Enum format = bgfx::TextureFormat::Enum::R8;
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

			Character character = {
				handle,
				glm::ivec2(FTface->glyph->bitmap.width, FTface->glyph->bitmap.rows),
				glm::ivec2(FTface->glyph->bitmap_left, FTface->glyph->bitmap_top),
				FTface->glyph->advance.x
			};
			characters.insert(std::pair<char, Character>(c, character));
		}
		else {
			std::cout << "ERROR::FREETYTPE:FONT Failed to create Handle! |" << (char)c << std::endl;
		}
	}

	FT_Done_Face(FTface);
}

Font::~Font()
{
	
}
#include "TextRenderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Engine/AssetManagement/Font.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/Utilities/TypeConversion.h"

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Shader.h"

#include "Engine/Utilities/DebugMemory.h"

Shader* TextRenderer::_shader = nullptr;
bool TextRenderer::init = false;

void TextRenderer::destroy()
{
}

TextRenderer::TextRenderer()
{
	if (!init) {
		me::data::PositionColorUVVertex::init();
		//Replace with text shader
		_shader = AssetManager::get<Shader>("assets/shaders/vs_sprite.bin");
		init = true;
	}

	ibh = bgfx::createIndexBuffer(bgfx::makeRef(me::data::PositionColorUVVertex::indices, sizeof(me::data::PositionColorUVVertex::indices)));
	s_font = bgfx::createUniform("s_sprite", bgfx::UniformType::Sampler);
	_font = nullptr;
	_text = "";
	_vbs = std::vector < bgfx::VertexBufferHandle>();
	scale = 0.5f;
}

TextRenderer::~TextRenderer()
{
	bgfx::destroy(ibh);
	bgfx::destroy(s_font);
	clearVertexBuffers();
}

void TextRenderer::setFont(Font* font)
{
	_font = font;
	buildVertexBuffers();
}

void TextRenderer::setText(char* text)
{
	_text = text;
	buildVertexBuffers();
}

void TextRenderer::render()
{
	if (strlen(_text) > 0) {

		for (size_t i = 0; i < _vbs.size(); i++)
		{
			if (!bgfx::isValid(_vbs[i])) { continue; }
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_BLEND_ALPHA, BGFX_STATE_BLEND_ADD);
			bgfx::setTransform(glm::value_ptr(transform.getGlobalMatrix()));
			bgfx::setVertexBuffer(0, _vbs[i]);
			bgfx::setIndexBuffer(ibh);
			bgfx::setTexture(0, s_font, _font->getCharacter(_text[i]).Handle);
			bgfx::submit(0, _shader->getHandle());
		}
	}
}

void TextRenderer::clearVertexBuffers()
{
	for (size_t i = 0; i < _vbs.size(); i++)
	{
		if (bgfx::isValid(_vbs[i])) {
			bgfx::destroy(_vbs[i]);
		}
	}
	_vbs.clear();
}

void TextRenderer::buildVertexBuffers()
{
	if (_font == nullptr) { return; }
	//Clear out the old text
	float x = 0;
	float y = 0;
	glm::vec4 color = { 255,255,255, 255 };

	clearVertexBuffers();

	for (size_t i = 0; i < strlen(_text); i++)
	{
		if (_text[i] == '\n') {
			bgfx::VertexBufferHandle invVbh;
			invVbh.idx = BGFX_INVALID_HANDLE;
			_vbs.push_back(invVbh);

			//https://stackoverflow.com/questions/28009564/new-line-pixel-distance-in-freetype
			//Take a look at this to fix spacing

			Character ch = _font->getCharacter('T');
			x = 0;
			y -= (ch.size.y + 10);
		}
		else {
			Character ch = _font->getCharacter(_text[i]);

			float xpos = x + ch.bearing.x;
			float ypos = y - (ch.size.y - ch.bearing.y);

			float w = ch.size.x;
			float h = ch.size.y;

			me::data::PositionColorUVVertex lineData[4];
			//lineData[0] = TextVertex{ xpos, ypos, 0.0f, Utility::colorToHex(color), 0, 0x7fff };
			//lineData[1] = TextVertex{ xpos + w, ypos, 0.0f, Utility::colorToHex(color), 0x7fff, 0x7fff };
			//lineData[2] = TextVertex{ xpos + w, ypos + h, 0.0f, Utility::colorToHex(color),  0x7fff, 0 };
			//lineData[3] = TextVertex{ xpos, ypos + h, 0.0f, Utility::colorToHex(color), 0, 0 };
			memcpy(lineData, me::data::PositionColorUVVertex::verts, sizeof(me::data::PositionColorUVVertex::verts));
			lineData[0].xy({ xpos, ypos });
			lineData[1].xy({ xpos + w, ypos });
			lineData[2].xy({ xpos + w, ypos + h });
			lineData[3].xy({ xpos, ypos + h });

			bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::copy(lineData, sizeof(lineData)), me::data::PositionColorUVVertex::layout);

			_vbs.push_back(vbh);
			x += (ch.advance >> 6);
		}
	}
}

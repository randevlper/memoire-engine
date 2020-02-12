#include "TextRenderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Engine/AssetManagement/Font.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/Utilities/TypeConversion.h"

bgfx::VertexLayout TextVertex::pcvLayout;
TextVertex TextVertex::planeVerts[] = {
	{-1.0f, -1.0f, 0.0f, 0xffffffff, 0, 0x7fff},
	{1.0f, -1.0f, 0.0f, 0xffffffff, 0x7fff, 0x7fff},
	{1.0f, 1.0f, 0.0f, 0xffffffff, 0x7fff, 0},
	{-1.0f, 1.0f, 0.0f, 0xffffffff, 0, 0}
};
const uint16_t TextVertex::planeTriList[] = {
	0,1,2,
	0,2,3
};

void TextVertex::init() {
	pcvLayout.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
		.end();
}

bgfx::ProgramHandle TextRenderer::s_program;
bool TextRenderer::init = false;

TextRenderer::TextRenderer()
{
	if (!init) {
		TextVertex::init();
		s_program = FileUtility::loadProgram("assets/shaders/vs_sprite.bin",
			"assets/shaders/fs_sprite.bin");
		init = true;
	}

	ibh = bgfx::createIndexBuffer(bgfx::makeRef(TextVertex::planeTriList, sizeof(TextVertex::planeTriList)));
	s_font = bgfx::createUniform("s_font", bgfx::UniformType::Sampler);
	_font = nullptr;
	_text = "";
	_tvbs = std::vector < bgfx::TransientVertexBuffer>();
}

TextRenderer::~TextRenderer()
{
	bgfx::destroy(ibh);
	bgfx::destroy(s_font);
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
		bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_BLEND_ALPHA, BGFX_STATE_BLEND_ADD);
		bgfx::setTransform(glm::value_ptr(transform.getGlobalMatrix()));
		//bgfx::setVertexBuffer(0, vbh);
		bgfx::setIndexBuffer(ibh);
		bgfx::setTexture(0, s_font, textureHandle);
		//bgfx::setUniform(s_world, glm::value_ptr(transform.getGlobalMatrix()));


		bgfx::submit(0, s_program);
	}
}

void TextRenderer::buildVertexBuffers()
{
	if (_font == nullptr) { return; }
	//Clear out the old text
	float x = 0;
	float y = 0;
	glm::vec4 color = { 255,255,255, 255 };

	for (size_t i = 0; i < strlen(_text); i++)
	{
		Character ch = _font->getCharacter(_text[i]);

		float xpos = x + ch.bearing.x;
		float ypos = y - (ch.size.y - ch.bearing.y);

		float w = ch.size.x;
		float h = ch.size.y;

		bgfx::TransientVertexBuffer tvb;
		bgfx::allocTransientVertexBuffer(&tvb, 4, LineVertex::layout);
		TextVertex* lineData = (TextVertex*)tvb.data;
		lineData[0] = TextVertex{ xpos, ypos, 0.0f, Utility::colorToHex(color), 0, 0x7fff };
		lineData[1] = TextVertex{ xpos + w, ypos, 0.0f, Utility::colorToHex(color), 0x7fff, 0x7fff };
		lineData[2] = TextVertex{ xpos + w, ypos + h, 0.0f, Utility::colorToHex(color),  0x7fff, 0 };
		lineData[3] = TextVertex{ xpos, ypos + h, 0.0f, Utility::colorToHex(color), 0, 0 };
		_tvbs.push_back(tvb);

	}
}

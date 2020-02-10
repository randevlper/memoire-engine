#include "TextRenderer.h"
#include "Engine/AssetManagement/Font.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/FileUtility.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

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

	vbh = bgfx::createVertexBuffer(bgfx::makeRef(TextVertex::planeVerts, sizeof(TextVertex::planeVerts)), TextVertex::pcvLayout);
	ibh = bgfx::createIndexBuffer(bgfx::makeRef(TextVertex::planeTriList, sizeof(TextVertex::planeTriList)));
	s_font = bgfx::createUniform("s_font", bgfx::UniformType::Sampler);
	_font = nullptr;
	_text = "";
}

TextRenderer::~TextRenderer()
{
	bgfx::destroy(vbh);
	bgfx::destroy(ibh);
	bgfx::destroy(s_font);
}

void TextRenderer::setFont(Font* font)
{
	bgfx::destroy(vbh);

}

void TextRenderer::setText(char* text)
{

}

void TextRenderer::render()
{
	if (strlen(_text) > 0) {
		bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_BLEND_ALPHA, BGFX_STATE_BLEND_ADD);
		bgfx::setTransform(glm::value_ptr(transform.getGlobalMatrix()));
		bgfx::setVertexBuffer(0, vbh);
		bgfx::setIndexBuffer(ibh);
		bgfx::setTexture(0, s_font, textureHandle);
		//bgfx::setUniform(s_world, glm::value_ptr(transform.getGlobalMatrix()));


		bgfx::submit(0, s_program);
	}
}
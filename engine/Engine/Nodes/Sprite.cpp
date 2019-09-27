#include "Sprite.h"
#include "bgfx/bgfx.h"
#include "Engine/Core/FileUtility.h"

bgfx::VertexLayout SpriteVertex::pcvLayout;
SpriteVertex SpriteVertex::planeVerts[] = {
	{-1.0f, -1.0f, 0.0f, 0xffffffff, 0, 0x7fff},
	{1.0f, -1.0f, 0.0f, 0xffffffff, 0x7fff, 0x7fff},
	{1.0f, 1.0f, 0.0f, 0xffffffff, 0x7fff, 0},
	{-1.0f, 1.0f, 0.0f, 0xffffffff, 0, 0}
};
const uint16_t SpriteVertex::planeTriList[] = {
	0,1,2,
	0,2,3
};

void SpriteVertex::init(){
	pcvLayout.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
		.end();
}

bgfx::ProgramHandle Sprite::s_program;
bool Sprite::init = false;
Sprite::Sprite()
{
	if (!init) {
		SpriteVertex::init();
		s_program = FileUtility::loadProgram("assets/shaders/vs_sprite.bin",
			"assets/shaders/fs_sprite.bin");
		init = true;
	}

	vbh = bgfx::createVertexBuffer(bgfx::makeRef(SpriteVertex::planeVerts, sizeof(SpriteVertex::planeVerts)), SpriteVertex::pcvLayout);
	ibh = bgfx::createIndexBuffer(bgfx::makeRef(SpriteVertex::planeTriList, sizeof(SpriteVertex::planeTriList)));
	s_sprite = bgfx::createUniform("s_sprite", bgfx::UniformType::Sampler);
}

Sprite::~Sprite()
{

}

void Sprite::destroy()
{
	bgfx::destroy(vbh);
	bgfx::destroy(ibh);
	bgfx::destroy(s_sprite);
}

void Sprite::render()
{
	bgfx::setVertexBuffer(0, vbh);
	bgfx::setIndexBuffer(ibh);
	bgfx::setTexture(0, s_sprite, texture);
	bgfx::submit(0, s_program);
}

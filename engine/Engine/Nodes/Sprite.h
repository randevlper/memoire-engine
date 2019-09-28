#pragma once

#include "Node.h"
#include "bgfx/bgfx.h"

struct SpriteVertex
{
	float x;
	float y;
	float z;
	uint32_t abgr;
	int16_t m_u;
	int16_t m_v;
	static bgfx::VertexLayout pcvLayout;
	static SpriteVertex planeVerts[];
	static const uint16_t planeTriList[];
	static void init();
};

class Sprite : public Node
{
public:
	Sprite();
	~Sprite();
	/*
	Texture
	*/
	bgfx::TextureHandle texture;
	void destroy();
	void render();

private:
	bgfx::VertexBufferHandle vbh;
	bgfx::IndexBufferHandle ibh;
	bgfx::UniformHandle s_sprite;
	bgfx::UniformHandle s_world;
	static bgfx::ProgramHandle s_program;
	static bool init;
};

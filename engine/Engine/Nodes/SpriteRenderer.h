#pragma once
#include "Engine/Nodes/Node.h"
#include <bgfx/bgfx.h>
class Sprite;
class Shader;

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

class SpriteRenderer : public Node
{
public:
	SpriteRenderer();
	~SpriteRenderer() override;

	void setSprite(Sprite* sprite);
	Sprite* getSprite();
	void render();
	static void destroy();

private:
	Sprite* _sprite;
	SpriteVertex newVerts[4];
	bgfx::VertexBufferHandle vbh;
	bgfx::IndexBufferHandle ibh;
	bgfx::UniformHandle s_sprite;

	static Shader* shader;
	static bool init;
};
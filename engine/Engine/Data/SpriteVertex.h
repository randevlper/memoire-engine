#pragma once
#include <cstdint>

namespace bgfx {
	struct VertexLayout;
}

struct SpriteVertex
{
	float x;
	float y;
	float z;
	uint32_t abgr;
	int16_t m_u;
	int16_t m_v;
	static bgfx::VertexLayout* pcvLayout;
	static SpriteVertex planeVerts[];
	static const uint16_t planeTriList[];
	static void init();
};
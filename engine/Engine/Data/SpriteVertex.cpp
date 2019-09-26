#include "SpriteVertex.h"
#include "bgfx/bgfx.h"


bgfx::VertexLayout* SpriteVertex::pcvLayout = nullptr;
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

void SpriteVertex::init() {
	if (pcvLayout != nullptr) {
		pcvLayout = new bgfx::VertexLayout();
		pcvLayout->begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
			.end();
	}
}
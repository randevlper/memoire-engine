#include "VertexTypes.h"

namespace me {
	namespace data {
		bgfx::VertexLayout PositionUVVertex::pcvLayout;
		bool PositionUVVertex::isInit = false;

		PositionUVVertex PositionUVVertex::planeVerts[] = {
			{0.0f, 0.0f, 0.0f, 0, 0x7fff},
			{1.0f, 0.0f, 0.0f, 0x7fff, 0x7fff},
			{1.0f, 1.0f, 0.0f, 0x7fff, 0},
			{0.0f, 1.0f, 0.0f, 0, 0}
		};

		const uint16_t PositionUVVertex::planeTriList[] = {
			0,1,2,
			0,2,3
		};

		void PositionUVVertex::init()
		{
			if (!isInit) {
				isInit = true;
				pcvLayout.begin()
					.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
					.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
					.end();
			}
			
		}

		bool PositionColorUVVertex::isInit = false;
		bgfx::VertexLayout PositionColorUVVertex::pcvLayout;
		PositionColorUVVertex PositionColorUVVertex::planeVerts[] = {
			{0.0f, 0.0f, 0.0f, 0xffffffff, 0, 0x7fff},
			{1.0f, 0.0f, 0.0f, 0xffffffff, 0x7fff, 0x7fff},
			{1.0f, 1.0f, 0.0f, 0xffffffff, 0x7fff, 0},
			{0.0f, 1.0f, 0.0f, 0xffffffff, 0, 0}
		};

		const uint16_t PositionColorUVVertex::planeTriList[] = {
			0,1,2,
			0,2,3
		};

		void PositionColorUVVertex::init() {
			if (!isInit) {
				pcvLayout.begin()
					.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
					.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
					.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
					.end();
			}
		}
	}
}



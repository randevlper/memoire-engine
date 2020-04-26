#pragma once
#include <bgfx/bgfx.h>
#include <glm/vec2.hpp>

//These should be used instead of creating a new one for each class
namespace me {
	namespace data {
		struct PositionUVVertex
		{
			float x;
			float y;
			float z;
			int16_t m_u;
			int16_t m_v;

			void xy(glm::vec2 value) {
				x = value.x;
				y = value.y;
			}

			static bgfx::VertexLayout pcvLayout;
			static PositionUVVertex planeVerts[4];
			static const uint16_t planeTriList[6];
			static void init();
			static bool isInit;
		};

		struct PositionColorUVVertex
		{
			float x;
			float y;
			float z;
			uint32_t abgr;
			int16_t m_u;
			int16_t m_v;

			void xy(glm::vec2 value) {
				x = value.x;
				y = value.y;
			}

			static bgfx::VertexLayout pcvLayout;
			static PositionColorUVVertex planeVerts[4];
			static const uint16_t planeTriList[6];
			static void init();
			static bool isInit;
		};

		struct PositionColorVertex
		{
			float x;
			float y;
			float z;
			unsigned int abgr;
			static bgfx::VertexLayout layout;
			static const unsigned short planeIndexList[6];
			static void init();
			static bool isInit;
		};
	}
}
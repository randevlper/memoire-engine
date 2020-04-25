#pragma once
#include "Engine/Nodes/Node.h"

#include <bgfx/bgfx.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class Shader;

namespace me {
	namespace ui {
		struct ButtonVertex
		{
			float x;
			float y;
			float z;
			int16_t m_u;
			int16_t m_v;
			static bgfx::VertexLayout pcvLayout;
			static ButtonVertex planeVerts[];
			static const uint16_t planeTriList[];
			static void init();
		};


		class Button : public Node2D
		{
		public:
			Button();
			~Button() override;

			bool isMouseOver(glm::vec2 mousePos);

			void setSize(glm::vec2 size);
			void setColor(glm::vec4 rgba);
			void render();

			static void destroy();

		private:

			static bool _isInit;
			static Shader* _shader;

			glm::vec2 _size;
			glm::vec4 _color;

			ButtonVertex _verts[4];

			bgfx::UniformHandle _u_color;
			bgfx::VertexBufferHandle _vbh;
			bgfx::IndexBufferHandle _ibh;
		};
	}
}


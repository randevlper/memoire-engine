#pragma once
#include "Engine/UI/NodeUI.h"

#include <functional>

#include <bgfx/bgfx.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class Shader;

namespace me {
	namespace ui {

		//Should move these vertex data to diffrent files
		struct ButtonVertex
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
			static ButtonVertex planeVerts[];
			static const uint16_t planeTriList[];
			static void init();
			
		};


		class Button : public NodeUI
		{
		public:
			Button();
			~Button() override;

			void sendMouseInfo(glm::vec2 mousePos, bool isClicking);
			void setSize(glm::vec2 size);
			
			void render();

			//Normal Color
			glm::vec4 colorNormal;
			//Hover Color
			glm::vec4 colorHightlight;
			//Click Color
			glm::vec4 colorClicked;
			//Disabled Color
			glm::vec4 colorDisabled;

			std::function<void()> onClick;
				
		private:

			static bool _isInit;
			static Shader* _shader;

			bool _lastIsMouseOver;
			bool _currentIsMouseOver;
			bool _lastMouseClicking;
			bool _currentMouseClicking;

			glm::vec2 _size;
			glm::vec4 _color;

			ButtonVertex _verts[4];

			bgfx::UniformHandle _u_color;
			bgfx::VertexBufferHandle _vbh;
			bgfx::IndexBufferHandle _ibh;
		
			void setColor(glm::vec4 rgba);
		
		};
	}
}


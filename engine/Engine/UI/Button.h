#pragma once
#include "Engine/UI/NodeUI.h"

#include <functional>

#include <bgfx/bgfx.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Engine/Data/VertexTypes.h"

class Shader;

namespace me {
	namespace ui {

		class Button : public NodeUI
		{
		public:
			Button();
			~Button() override;

			void sendMouseInfo(glm::vec2 mousePos, bool isClicking);
			void setSize(glm::vec2 size);
			
			void render() override;

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

			me::data::PositionUVVertex _verts[4];

			bgfx::UniformHandle _u_color;
			bgfx::VertexBufferHandle _vbh;
			bgfx::IndexBufferHandle _ibh;
		
			void setColor(glm::vec4 rgba);
		
		};
	}
}


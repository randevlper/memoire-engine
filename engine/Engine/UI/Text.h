#pragma once
#include "NodeUI.h"

#include <string>
#include <vector>

#include <bgfx/bgfx.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class Font;
class Shader;

namespace me {
	namespace ui {
		class Text : public NodeUI
		{
		public:
			Text();
			~Text() override;

			
			//Expected 0 - 255
			void setColor(glm::vec4 value);

			//value from 0.0 - 1.0
			void setPercentRender(float value);

			//Does not support rotation
			void render() override;
			void setFont(Font* font);
			void setText(std::string value);

		private:
			std::vector<bgfx::VertexBufferHandle> _vbs;
			bgfx::IndexBufferHandle _ibh;
			bgfx::UniformHandle _u_sprite;
			bgfx::UniformHandle _u_color;

			Font* _font;
			std::string _text;
			float _percentRender;
			glm::vec4 _color;

			static Shader* _shader;
			static bool _isInit;

			void buildVertexBuffers();
			void clearVertexBuffers();

		};
	}
}
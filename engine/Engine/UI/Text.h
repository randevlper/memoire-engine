#pragma once
#include "NodeUI.h"

#include <bgfx/bgfx.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace me {
	namespace ui {
		class Text : public NodeUI
		{
		public:
			Text();
			~Text() override;

			glm::vec4 color;


		private:

		};
	}
}
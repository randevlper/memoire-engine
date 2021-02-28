#pragma once
#include "glm/glm.hpp"

namespace Utility {
	static unsigned int colorToHex(glm::vec4& color) {
		return (int)color.a << 24 | (int)color.b << 16 | (int)color.g << 8 | (int)color.r << 0;
	}
}

namespace me {
	namespace util {
		glm::vec2 convertPixelToScreen(glm::ivec2 value);
		glm::vec2 convertInputToScreen(glm::ivec2 value);
		glm::vec2 convertScreenToWorld(glm::vec2 value);
	}
}
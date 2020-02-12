#pragma once
#include "glm/glm.hpp"

namespace Utility {
	static unsigned int colorToHex(glm::vec4& color) {
		return (int)color.a << 24 | (int)color.b << 16 | (int)color.g << 8 | (int)color.r << 0;
	}
}
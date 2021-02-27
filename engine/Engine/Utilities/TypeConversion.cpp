#include "TypeConversion.h"

#include "Engine/Core/Context.h"

namespace me {
	namespace util {

		/*
		Expects Width 0 - ScreenWidth
		Expects Height 0 - ScreenHeight
		*/
		glm::vec2 convertPixelToScreen(glm::ivec2 value) {
			glm::vec2 retval;

			retval.x = value.x / (float)Context::getRenderWidth();
			retval.y = value.y / (float)Context::getRenderHeight();

			//Should check here what the renderer is expecting in screen cords
			//OpenGL uses -1 to 1

			//OpenGL
			retval.x = (retval.x * 2) - 1;
			retval.y = (retval.y * 2) - 1;

			return retval;
		}
	}
}
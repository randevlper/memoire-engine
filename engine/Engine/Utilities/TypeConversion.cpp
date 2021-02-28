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

		glm::vec2 convertInputToScreen(glm::ivec2 value) {
			glm::vec2 retval;

			retval.x = value.x / (float)Context::getWindowWidth();
			retval.y = value.y / (float)Context::getWindowHeight();

			//Should check here what the renderer is expecting in screen cords
			//OpenGL uses -1 to 1

			//OpenGL
			retval.x = (retval.x * 2) - 1;
			retval.y = (retval.y * 2) - 1;

			return retval;
		}

		glm::vec2 convertScreenToWorld(glm::vec2 value)
		{
			glm::vec2 retval = value;
			retval.y *= -1;
			retval.x += 1;
			retval.y += 1;
			retval.x = retval.x * 0.5f * (float)Context::getRenderWidth();
			retval.y = retval.y * 0.5f * (float)Context::getRenderHeight();
			

			return retval;
		}
	}
}
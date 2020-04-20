#include "Engine/Core/Context.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/Core/Renderer.h"
#include "glm/vec2.hpp"
#include "SDL_events.h"
#include "SDL_pixels.h"
#include "Engine/Core/Physics.h"
#include "Engine/Data/AseData.h"
//#include "Engine/Tools/aseprite.h"
#include "Engine/Core/Input.h"
#include "Engine/Data/Transform.h"
#include "Engine/Utilities/Debug.h"
#include "glm/gtx/perpendicular.hpp"


//Severely out of date
int main()
	{
		ContextWindowParems cWinParems = { "Ayse why.", 1280, 720, 640, 360, 60 };
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}

		Transform test1;
		test1.setLocalPosition(glm::vec2(10, 10));
		Transform test2;
		test2.setLocalScale(glm::vec2(10, 10));
		test1.setParent(&test2);

		assert(test1.getPosition() == glm::vec2(100, 100));
		assert(test1.getPosition() != glm::vec2(101, 100));


		assert(glm::normalize(glm::vec2(10, 0)) == glm::vec2(1, 0));
		std::vector<glm::vec2> points;
		points.push_back(glm::vec2(1, 1));
		points.push_back(glm::vec2(-1, 1));
	}
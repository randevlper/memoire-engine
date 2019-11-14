#include "Debug.h"

#include "Engine/Core/Context.h"
#include "Engine/Data/Transform.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Nodes/Node.h"
#include "glm/vec4.hpp"
#include "glm/vec2.hpp"

#include "SDL.h"
#include <iostream>

void Debug::Log(char* value)
{
	std::cout << "[" << SDL_GetTicks() << "] " << value << std::endl;
}

void Debug::DrawTransform(Transform* t)
{
	glm::mat3x3 m = t->getGlobalMatrix();
	glm::vec2 pos = { m[2].x, m[2].y };
	glm::vec2 right = pos + glm::vec2{m[0].x, m[0].y};
	glm::vec2 up = pos + glm::vec2{ m[1].x, m[1].y };

	Renderer::renderLine(pos, right, glm::vec4{ 255, 0, 0, 255 });
	Renderer::renderLine(pos, up, glm::vec4{ 0, 255, 0, 255 });
}

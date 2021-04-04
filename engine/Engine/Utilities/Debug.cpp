#include "Debug.h"

#include <sstream>

#include "Engine/Core/Context.h"
#include "Engine/Data/Transform.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Nodes/Node.h"
#include "glm/vec4.hpp"
#include "glm/vec2.hpp"
#include "glm/mat3x3.hpp"

#include "SDL.h"
#include <iostream>

void Debug::Log(std::string* values, size_t count)
{
	std::ostringstream log;
	for (size_t i = 0; i < count; i++)
	{
		log << values[i];
	}
	Debug::Log(log.str());
}

void Debug::Log(std::string value)
{
	std::cout << "[" << SDL_GetTicks() << "] " << value << std::endl;
}

void Debug::LogError(std::string value)
{
	Log("[Error]" + value);
}

void Debug::LogError(std::string* values, size_t count)
{
	std::ostringstream log;
	for (size_t i = 0; i < count; i++)
	{
		log << values[i];
	}
	Debug::LogError(log.str());
}

void Debug::DrawTransform(Transform* t)
{
	float length = 5;

	glm::mat4x4 m = t->getGlobalMatrix();
	glm::vec2 pos = { m[3].x, m[3].y };
	glm::vec2 right = pos + glm::vec2{m[0].x * 5, m[0].y * 5};
	glm::vec2 up = pos + glm::vec2{ m[1].x * 5, m[1].y * 5 };

	Renderer::renderLine(pos, right, glm::vec4{ 255, 0, 0, 255 });
	Renderer::renderLine(pos, up, glm::vec4{ 0, 255, 0, 255 });
}

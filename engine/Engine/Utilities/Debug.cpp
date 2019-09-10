#include "Debug.h"

#include "Engine/Core/Context.h"
#include "Engine/Data/Transform.h"
#include "Engine/Core/Renderer.h"

#include "SDL.h"
#include <iostream>

void Debug::Log(char* value)
{
	std::cout << value << std::endl;
}

void Debug::DrawTransform(Transform* t)
{
	glm::mat3x3 m = t->getGlobalMatrix();
	glm::vec2 pos = { m[2].x, m[2].y };
	glm::vec2 right = pos + glm::vec2{m[0].x, m[0].y};
	glm::vec2 up = pos + glm::vec2{ m[1].x, m[1].y };

	SDL_Color red{ 255,0,0 };

	SDL_Rect rect;
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = 10;
	rect.h = 10;
	SDL_Color color;
	color = { 255,0,0,255 };

	//Renderer::renderSquare(rect, color);

	SDL_SetRenderDrawColor(Context::getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawLine(Context::getRenderer(), pos.x, pos.y, right.x, right.y);
	
	SDL_SetRenderDrawColor(Context::getRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawLine(Context::getRenderer(), pos.x, pos.y, up.x, up.y);
	
}

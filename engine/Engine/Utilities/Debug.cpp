#include "Debug.h"

#include "Engine/Core/Context.h"
#include "Engine/Data/Transform.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Nodes/Node.h"
#include "Engine/Nodes/Collider.h"

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

	Renderer::renderLine(pos, right, SDL_Color{ 255, 0, 0, 255 });
	Renderer::renderLine(pos, up, SDL_Color{ 0, 255, 0, 255 });
}

void Debug::DrawCollider(Collider* col) {
	SATGeometry g = col->getWorldGeo();
	SDL_Point points[COLLIDER_MAX_POINTS];
	for (size_t i = 0; i < g.points.size(); i++)
	{
		points[i] = SDL_Point{ (int)g.points[i].x, (int)g.points[i].y};
	}
	points[g.points.size()] = SDL_Point{ (int)g.points[0].x, (int)g.points[0].y };

	Renderer::renderLines(points, col->geo.points.size() + 1, (col->isStatic ? SDL_Color{255,0,0,255} : SDL_Color{ 0, 255, 0, 255 }));
}

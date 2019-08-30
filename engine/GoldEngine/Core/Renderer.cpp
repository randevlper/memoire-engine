#include "GoldEngine/Core/Renderer.h"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include "SDL.h"
#include "GoldEngine/Data/SpriteData.h"
#include "GoldEngine/Data/AseData.h"
#include "GoldEngine/Core/Context.h"
#include "GoldEngine/Utilities/Timer.h"
#include "Box2D/Box2D.h"
#include "Box2D/Common/b2Settings.h"
#include "GoldEngine/Utilities/b2dtoSDL.h"

glm::vec2* Renderer::_cameraPos = new glm::vec2();
Renderer* Renderer ::_instance = nullptr;
Timer Renderer::_fpsTimer = Timer();
Timer Renderer::_capTimer = Timer();
Uint64 Renderer::_frameCount = 0;

void Renderer::init()
{
	if (_instance == nullptr) {
		_instance = new Renderer();
		_fpsTimer.start();
	}
}

void Renderer::quit()
{
	if (_instance != nullptr) {
		_fpsTimer.stop();
		delete(_instance);
	}
}

void Renderer::tick()
{
	_capTimer.start();
}

void Renderer::renderLines(SDL_Point* points, int pointsCount, SDL_Color& color)
{
	for (size_t i = 0; i < pointsCount; i++)
	{
		points[i].x -= _cameraPos->x;
		points[i].y -= _cameraPos->y;
	}
	SDL_SetRenderDrawColor(Context::getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawLines(Context::getRenderer(), points, pointsCount);
}

void Renderer::renderSquare(SDL_Rect& rect, SDL_Color& color)
{
	rect.x -= _cameraPos->x;
	rect.y -= _cameraPos->y;
	SDL_SetRenderDrawColor(Context::getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(Context::getRenderer(), &rect);
}

void Renderer::renderb2Body(b2Body* body)
{
	b2Fixture* f = body->GetFixtureList();
	b2EdgeShape* edge;
	int32 num;
	switch (f->GetType())
	{
	case b2Shape::Type::e_chain: {
		b2ChainShape* chain = (b2ChainShape*)f->GetShape();
		break;
	}
	case b2Shape::Type::e_circle: {
		b2CircleShape* circle = (b2CircleShape*)f->GetShape();
		SDL_Point points[9];
		points[0] = toSDL(body->GetWorldPoint(circle->m_p + b2Vec2(0, circle->m_radius)));

		b2Vec2 topRight = b2Vec2(1, 1);
		topRight.Normalize();
		topRight.x *= circle->m_radius;
		topRight.y *= circle->m_radius;
		points[1] = toSDL(body->GetWorldPoint(topRight));

		points[2] = toSDL(body->GetWorldPoint(circle->m_p + b2Vec2(circle->m_radius, 0)));

		b2Vec2 bottomRight = b2Vec2(1, -1);
		bottomRight.Normalize();
		bottomRight.x *= circle->m_radius;
		bottomRight.y *= circle->m_radius;
		points[3] = toSDL(body->GetWorldPoint(bottomRight));

		points[4] = toSDL(body->GetWorldPoint(circle->m_p + b2Vec2(0, -circle->m_radius)));

		b2Vec2 bottomLeft = b2Vec2(-1, -1);
		bottomLeft.Normalize();
		bottomLeft.x *= circle->m_radius;
		bottomLeft.y *= circle->m_radius;
		points[5] = toSDL(body->GetWorldPoint(bottomLeft));

		points[6] = toSDL(body->GetWorldPoint(circle->m_p + b2Vec2(-circle->m_radius, 0)));

		b2Vec2 topLeft = b2Vec2(-1, 1);
		topLeft.Normalize();
		topLeft.x *= circle->m_radius;
		topLeft.y *= circle->m_radius;
		points[7] = toSDL(body->GetWorldPoint(topLeft));

		points[8] = toSDL(body->GetWorldPoint(circle->m_p + b2Vec2(0, circle->m_radius)));
		SDL_Color c = {255, 0, 0, 255};
		renderLines(points, 9, c);
		break;
	}
	case b2Shape::Type::e_edge: {
		b2EdgeShape* edge = (b2EdgeShape*)f->GetShape();
		break;
	}
	case b2Shape::Type::e_polygon: {
		SDL_Point points[b2_maxPolygonVertices];
		b2PolygonShape* polygon = (b2PolygonShape*)f->GetShape();
		for (size_t i = 0; i < polygon->m_count; i++)
		{
			points[i] = toSDL(body->GetWorldPoint(polygon->m_vertices[i]));
		}
		points[polygon->m_count] = toSDL(body->GetWorldPoint(polygon->m_vertices[0]));

		//TODO adding precomputed widths/heights for speed
		SDL_Rect rect = { points[0].x, points[0].y, 4, 4};
		glm::vec2 point1 = { points[0].x, points[0].y };
		glm::vec2 point2 = { points[1].x, points[1].y };
		glm::vec2 point3 = { points[2].x, points[2].y };
		rect.w = glm::length(point2 - point1);
		rect.h = glm::length(point3 - point2);

		SDL_Color color = { 255, 0, 0, 100 };
		renderSquare(rect, color);
		color = { 255, 0, 0, 150 };
		renderLines(points, polygon->m_count + 1, color);
		
		break;
	}
	default:
		break;
	}
}

void Renderer::renderAseFrame(int x, int y, AseFrame* frame)
{
	for (size_t i = 0; i < frame->sprites.size(); i++)
	{
		renderAseSprite(x, y, &frame->sprites[i]);
	}
}

void Renderer::renderAseSprite(int x, int y, AseSprite* ase)
{
	SDL_Rect renderQuad = {(x + ase->xPos)  - _cameraPos->x, (y + ase->yPos) - _cameraPos->y, ase->width, ase->height };
	SDL_SetRenderDrawColor(Context::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(Context::getRenderer(), ase->texture, nullptr, &renderQuad);
}

void Renderer::renderSprite(glm::vec2& pos, SpriteData* spriteData)
{
	renderSprite(pos.x, pos.y, spriteData);
}

void Renderer::renderSprite(int x, int y, SpriteData* spriteData)
{
	SDL_Rect renderQuad = { x - _cameraPos->x, y - _cameraPos->y, spriteData->width, spriteData->height };
	SDL_SetRenderDrawColor(Context::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(Context::getRenderer(), spriteData->texture, nullptr, &renderQuad);
}

void Renderer::clearRenderer(SDL_Color& color)
{
	clearRenderer(color.r, color.g, color.b, color.a);
}

void Renderer::clearRenderer(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(Context::getRenderer(), r, g, b, a);
	SDL_RenderClear(Context::getRenderer());
}

void Renderer::render()
{
	//SDL_Log("FPS: %f", _frameCount / ( _fpsTimer.getTicks() / 1000.f));

	char title[80] = {};

	strcpy(title, Context::getWindowTitle());
	strcat(title, "FPS: ");
	//strcat(title, (_frameCount / (_fpsTimer.getTicks() / 1000.f)));
		//+  + (_frameCount / (_fpsTimer.getTicks() / 1000.f));

	Context::setWindowTitle(title);
	SDL_RenderPresent(Context::getRenderer());
	_frameCount++;

	//if frame finished early
	Uint32 frameTicks = _capTimer.getTicks();
	if (frameTicks < (1000 / Context::getMaxFps())) {
		SDL_Delay((1000 / Context::getMaxFps()) - frameTicks);
	}
}

void Renderer::setCameraPos(int x, int y)
{
	_cameraPos->x = x - (Context::getWindowWidth()/2);
	_cameraPos->y = y - (Context::getWindowHeight()/2);
}

glm::vec2 Renderer::getCameraPos()
{
	return *_cameraPos;
}

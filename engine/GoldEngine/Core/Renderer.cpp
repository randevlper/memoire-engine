#include "GoldEngine/Core/Renderer.h"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include "SDL_render.h"
#include "SDL_pixels.h"
#include "GoldEngine/Data/SpriteData.h"
#include "GoldEngine/Core/Context.h"
#include "Box2D/Box2D.h"
#include "Box2D/Common/b2Settings.h"

void Renderer::renderSquare(SDL_Rect& rect, SDL_Color& color)
{
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
			b2Vec2 wp = body->GetWorldPoint(polygon->m_vertices[i]);
			points[i] = { (int)wp.x,(int)wp.y };
		}
		b2Vec2 last = body->GetWorldPoint(polygon->m_vertices[0]);
		points[polygon->m_count] = { (int)last.x,(int)last.y };

		//TODO adding precomputed widths/heights for speed
		SDL_Rect rect = { points[0].x, points[0].y, 4, 4};
		glm::vec2 point1 = { points[0].x, points[0].y };
		glm::vec2 point2 = { points[1].x, points[1].y };
		glm::vec2 point3 = { points[2].x, points[2].y };
		rect.w = glm::length(point2 - point1);
		rect.h = glm::length(point3 - point2);

		SDL_Color color = { 255, 0, 0, 100 };
		renderSquare(rect, color);

		SDL_SetRenderDrawColor(Context::getRenderer(), 255, 0, 0, 150);
		SDL_RenderDrawLines(Context::getRenderer(), points, polygon->m_count + 1);
		break;
	}
	default:
		break;
	}
}

void Renderer::renderSprite(glm::vec2& pos, SpriteData* spriteData)
{
	renderSprite(pos.x, pos.y, spriteData);
}

void Renderer::renderSprite(int x, int y, SpriteData* spriteData)
{
	SDL_Rect renderQuad = { x, y, spriteData->width, spriteData->height };
	SDL_SetRenderDrawColor(Context::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(Context::getRenderer(), spriteData->texture, nullptr, &renderQuad);
}

void Renderer::clearRenderer(SDL_Color color)
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
	SDL_RenderPresent(Context::getRenderer());
}

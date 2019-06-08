#include "GoldEngine/Core/Renderer.h"
#include "glm/vec2.hpp"
#include "SDL_render.h"
#include "SDL_pixels.h"
#include "GoldEngine/Data/SpriteData.h"
#include "GoldEngine/Core/Context.h"
#include "Box2D/Box2D.h"
#include "Box2D/Common/b2Settings.h"

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
		//std::vector<Vector2> lines;
		for (size_t i = 0; i < polygon->m_count; i++)
		{
			b2Vec2 wp = body->GetWorldPoint(polygon->m_vertices[i]);
			points[i] = { (int)wp.x,(int)wp.y };
		}
		b2Vec2 last = body->GetWorldPoint(polygon->m_vertices[0]);
		points[polygon->m_count] = { (int)last.x,(int)last.y };



		SDL_SetRenderDrawColor(Context::getRenderer(), 255, 0, 0, 255);
		SDL_RenderDrawLines(Context::getRenderer(), points, polygon->m_count + 1);
		break;
	}
	default:
		break;
	}
}

void Renderer::renderSprite(glm::vec2 pos, SpriteData* spriteData)
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

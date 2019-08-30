#pragma once
#include "SDL_rect.h"
#include "Box2D/Common/b2Math.h"


SDL_Point& toSDL(b2Vec2& value) {
	SDL_Point ret = { value.x, value.y };
	return ret;
}
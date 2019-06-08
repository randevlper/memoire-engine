#pragma once
#include "glm/fwd.hpp"
struct SpriteData;
struct SDL_Color;
struct b2Body;

class Renderer
{
public:
	//Draw Line
	
	//Draw Square
	
	//Draw Physics Shape
	static void renderb2Body(b2Body* body);

	static void renderSprite(glm::vec2 pos, SpriteData* spriteData);
	static void renderSprite(int x, int y, SpriteData* spriteData);
	static void clearRenderer(SDL_Color color);
	static void clearRenderer(int r, int g, int b, int a);
	static void render();
private:

};
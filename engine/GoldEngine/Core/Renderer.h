#pragma once
#include "glm/fwd.hpp"
struct SpriteData;
struct SDL_Color;
struct SDL_Rect;
struct SDL_Point;
struct b2Body;
struct AseData;

class Renderer
{
public:
	//Draw Line
	static void renderLines(SDL_Point* points, int pointsCount, SDL_Color& color);

	//Draw Square
	static void renderSquare(SDL_Rect& rect, SDL_Color& color);

	//Draw Circle
	//static void renderCircle(glm::vec2& pos, float& radius);
	
	//Draw Physics Shape
	static void renderb2Body(b2Body* body);

	static void renderAse(int x, int y, AseData* ase);

	static void renderSprite(glm::vec2& pos, SpriteData* spriteData);
	static void renderSprite(int x, int y, SpriteData* spriteData);
	static void clearRenderer(SDL_Color color);
	static void clearRenderer(int r, int g, int b, int a);
	static void render();

	static void setCameraPos(int x, int y);
	static glm::vec2 getCameraPos();
private:
	static glm::vec2* _cameraPos;
};
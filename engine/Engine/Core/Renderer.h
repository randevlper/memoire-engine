#pragma once
#include "glm/fwd.hpp"
#include "SDL_stdinc.h"
struct SpriteData;
struct SDL_Color;
struct SDL_Rect;
struct SDL_Point;
struct AseSprite;
struct AseFrame;

class Timer;

class Renderer
{
public:
	static void init();
	static void quit();
	static void tick();
	//Draw Line
	static void renderLines(SDL_Point* points, int pointsCount, SDL_Color& color);

	//Draw Square
	static void renderSquare(SDL_Rect& rect, SDL_Color& color);

	//Draw Circle
	//static void renderCircle(glm::vec2& pos, float& radius);

	static void renderAseFrame(int x, int y, AseFrame* frame);
	static void renderAseSprite(int x, int y, AseSprite* ase);

	static void renderSprite(glm::vec2& pos, SpriteData* spriteData);
	static void renderSprite(int x, int y, SpriteData* spriteData);
	static void clearRenderer(SDL_Color& color);
	static void clearRenderer(int r, int g, int b, int a);
	static void render();

	static void setCameraPos(int x, int y);
	static glm::vec2 getCameraPos();
private:
	static glm::vec2* _cameraPos;
	static Renderer* _instance;
	static Timer _fpsTimer;
	static Timer _capTimer;
	static Uint64 _frameCount;
};
#pragma once

struct SpriteData;

class Renderer
{
public:
	static void renderSprite(int x, int y, SpriteData* spriteData);
	static void clearRenderer(int r, int g, int b, int a);
	static void render();
private:

};
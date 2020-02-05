#pragma once
#include "bgfx/bgfx.h"

class Sprite
{
public:
	Sprite();
	~Sprite();
	/*
	Texture
	*/
	bgfx::TextureHandle texture;
	int width, height;

private:
};

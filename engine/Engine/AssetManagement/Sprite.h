#pragma once
#include "bgfx/bgfx.h"

class Sprite
{
public:
	Sprite();
	Sprite(bgfx::TextureHandle handle, int width, int height);
	~Sprite();
	/*
	Texture
	*/
	bgfx::TextureHandle handle;
	int width, height;

private:
};

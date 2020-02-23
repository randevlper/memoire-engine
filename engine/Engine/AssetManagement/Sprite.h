#pragma once
#include <bgfx/bgfx.h>
#include "Asset.h"

class Sprite : public Asset
{
public:
	Sprite();
	Sprite(bgfx::TextureHandle handle, int width, int height);
	~Sprite() override;
	//~Asset() override;
	/*
	Texture
	*/
	bgfx::TextureHandle handle;
	int width, height;

private:
};

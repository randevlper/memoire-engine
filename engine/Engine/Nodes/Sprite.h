#pragma once

#include "Node.h"
#include "bgfx/bgfx.h"

class Sprite : public Node
{
public:
	Sprite();
	~Sprite();
	/*
	Texture
	*/
	bgfx::TextureHandle texture;

private:
};

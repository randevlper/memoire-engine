#include "Sprite.h"

Sprite::Sprite()
{
	handle.idx = -1;
	width = -1;
	height = -1;
}

Sprite::Sprite(bgfx::TextureHandle handle, int width, int height)
{
	this->handle = handle;
	this->width = width;
	this->height = height;
}

Sprite::~Sprite()
{
	bgfx::destroy(handle);
}

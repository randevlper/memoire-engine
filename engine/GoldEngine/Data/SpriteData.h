#pragma once

struct SDL_Texture;
struct SpriteData
{
	unsigned char* pixels;
	int width, height, orig_format, req_format;
	int depth, pitch, pixel_format;
	SDL_Texture* texture;
};
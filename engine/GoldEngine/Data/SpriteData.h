#pragma once

struct SDL_Texture;

namespace Aseprite {
	class AsepriteFile;
}

struct SpriteData
{
	unsigned char* pixels;
	int width, height, orig_format, req_format;
	int depth, pitch, pixel_format;
	SDL_Texture* texture;
};


struct AseData {
	Aseprite::AsepriteFile* aseFile;
	SDL_Texture* texture;
	int width, height;
};
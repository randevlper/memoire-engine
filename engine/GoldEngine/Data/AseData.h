#pragma once
#include <vector>
struct SDL_Texture;

namespace Aseprite {
	class AsepriteFile;
}

struct AseSprite {
	SDL_Texture* texture;
	int width, height;
	int xPos, yPos;
	int layerIndex;

	AseSprite(SDL_Texture* t, int w, int h, int x, int y, int l) {
		texture = t; width = w; height = h; xPos = x; yPos = y; layerIndex = l;
	}
};

struct AseFrame
{
	std::vector<AseSprite> sprites;

};

struct AseData {
	//TODO
	//Perlayer drawing

	Aseprite::AsepriteFile* aseFile;
	std::vector<AseFrame> frames;
};
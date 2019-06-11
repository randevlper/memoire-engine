#pragma once
#include <vector>
#include <string>
struct SDL_Texture;

namespace Aseprite {
	class AsepriteFile;
}

struct AseSprite {
	SDL_Texture* texture;
	int width, height;
	int xPos, yPos;
	int layerIndex;

	AseSprite(SDL_Texture* t, int w, int h, int x, int y, int l) :
		texture(t), width(w), height(h), xPos(x), yPos(y), layerIndex(l)
	{ }
};

struct AseFrame
{
	size_t frameDuration;
	std::vector<AseSprite> sprites;
};

struct AseAnimation
{
	std::string name;
	size_t from;
	size_t to;

	AseAnimation(std::string n, size_t f, size_t t) : name(n), from(f), to(t) {	}
};

struct AseData {
	//TODO
	//Perlayer drawing

	//Aseprite::AsepriteFile* aseFile;
	std::vector<AseFrame> frames;
	std::vector<AseAnimation> animations; //TODO get animation by name
};
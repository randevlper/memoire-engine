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
	double frameDuration;
	std::vector<AseSprite> sprites;
};

struct AseAnimation
{
	std::string name;
	std::vector<AseFrame*> frames;

	AseAnimation(std::string n) : name(n) {	}
	AseAnimation(AseAnimation(&a)) : name(a.name), frames(a.frames) {
	}

};

struct AseData {
	//TODO
	//Perlayer drawing

	//Aseprite::AsepriteFile* aseFile;
	std::vector<AseFrame> frames;
	std::vector<AseAnimation> animations; //TODO get animation by name
};
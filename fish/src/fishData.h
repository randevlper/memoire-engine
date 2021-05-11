#pragma once
#include <string>
#include "SDL_scancode.h"

struct FishData {
	int score;
	float speed;
	std::string spriteName;
	SDL_Scancode scancode;
	std::string scancodeName;
};
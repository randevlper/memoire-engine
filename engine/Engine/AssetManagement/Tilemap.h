#pragma once

#include <vector>

class Sprite;

struct Tile {
	unsigned int value;
};

class Tilemap
{
public:
	Tilemap();
	~Tilemap();

	void setWidth(unsigned int w) {
		width = w;
	}

	unsigned int getWidth() {
		return width;
	}

	void setHeight(unsigned int h) {
		height = h;
	}

	unsigned int getHeight() {
		return height;
	}

	std::vector<Tile> getTiles() {
		return tiles;
	}

	unsigned int size() {
		return height * width;
	}

	Sprite* testSprite;

	unsigned int tileWidth, tileHeight;

private:
	unsigned int width, height;
	
	std::vector<Tile> tiles;
};
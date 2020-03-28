#pragma once
#include <vector>

class Sprite;

struct Tile {
	Sprite* sprite;
	unsigned int index;
};

class Tilemap
{
public:
	Tilemap();
	~Tilemap();
	Tilemap(unsigned int width, unsigned int height);

	unsigned int getWidth() {
		return width;
	}
	unsigned int getHeight() {
		return height;
	}

	unsigned int size() {
		return height * width;
	}

	bool addTile(Tile value) {
		if (tiles.size() < (size_t)value.index + 1) {
			tiles.resize((size_t)value.index + 1);
		}

		tiles[value.index] = value;
		return true;
	}

	bool setTile(unsigned int index, unsigned int value) {
		if (value + 1 > tiles.size()) {
			return false;
		}

		if (index + 1 > map.size()) {
			return false;
		}

		map[index] = value;
	}

	Tile getTile(unsigned int index) {
		return tiles[map[index]];
	}


	Sprite* testSprite;

	unsigned int tileWidth, tileHeight;

private:
	unsigned int width, height;
	
	std::vector<Tile> tiles;
	std::vector<unsigned int> map;
};
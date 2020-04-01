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

	unsigned int getWidth();
	unsigned int getHeight();
	unsigned int getPixelWidth();
	unsigned int getPixelHeight();
	unsigned int getTileWidth();
	unsigned int getTileHeight();
	unsigned int size();

	void setTilemapSprite(Sprite* tilemap);
	Sprite* getTilemapSprite();
	void setTilesetSprite(Sprite* tileset);
	Sprite* getTilesetSprite();
private:
	//These values should be gotton from the tileset on creation
	unsigned int tileWidth, tileHeight;
	Sprite* tilemapSprite;
	Sprite* tilesetSprite;
};
#include "Tilemap.h"
#include "Sprite.h"

Tilemap::Tilemap() : 
	width(20) , height(20), 
	tileWidth(32), tileHeight(32), 
	testSprite(nullptr)
{
	tiles = std::vector<Tile>();
	map = std::vector<unsigned int>(width * height);
}

Tilemap::Tilemap(unsigned int width, unsigned int height) :
	width(width), height(height),
	tileWidth(32), tileHeight(32),
	testSprite(nullptr)
{
	tiles = std::vector<Tile>();
	map = std::vector<unsigned int>(width * height);
}

Tilemap::~Tilemap()
{
}
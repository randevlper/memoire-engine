#include "Tilemap.h"
#include "Sprite.h"

Tilemap::Tilemap() : 
	width(5) , height(5), 
	tileWidth(16), tileHeight(16), 
	testSprite(nullptr)
{
	tiles = std::vector<Tile>(width * height);
}

Tilemap::~Tilemap()
{
}
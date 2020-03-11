#include "Tilemap.h"
#include "Sprite.h"

Tilemap::Tilemap() : 
	width(5) , height(5), 
	tileWidth(32), tileHeight(32), 
	testSprite(nullptr)
{
	tiles = std::vector<Tile>(width * height);
}

Tilemap::~Tilemap()
{
}
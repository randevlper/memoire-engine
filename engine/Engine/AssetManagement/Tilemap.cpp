#include "Tilemap.h"
#include "Sprite.h"

Tilemap::Tilemap() : 
	tileWidth(32), tileHeight(32) //These values shold 
{

}

//TODO nullptr error checking

unsigned int Tilemap::getWidth() {
	return tilemapSprite->width;
}
unsigned int Tilemap::getHeight() {
	return tilemapSprite->height;
}

unsigned int Tilemap::getPixelWidth() {
	return tilemapSprite->width * tileWidth;
}

unsigned int Tilemap::getPixelHeight()
{
	return tilemapSprite->height * tileHeight;
}

unsigned int Tilemap::getTileWidth()
{
	return tileWidth;
}

unsigned int Tilemap::getTileHeight()
{
	return tileHeight;
}

unsigned int Tilemap::size() {
	return tilemapSprite->width * tilemapSprite->height;
}

void Tilemap::setTilemapSprite(Sprite* tilemap)
{
	tilemapSprite = tilemap;
}

Sprite* Tilemap::getTilemapSprite()
{
	return tilemapSprite;
}

void Tilemap::setTilesetSprite(Sprite* tileset)
{
	tilesetSprite = tileset;
}

Sprite* Tilemap::getTilesetSprite()
{
	return tilesetSprite;
}

Tilemap::~Tilemap()
{
}
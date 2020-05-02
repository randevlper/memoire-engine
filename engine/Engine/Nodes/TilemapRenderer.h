#pragma once

#include "Engine/Nodes/Node2D.h"

#include <vector>
#include <bgfx/bgfx.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class Shader;
class Tilemap;

#define ME_TILE_INVALID -1

class TilemapRenderer : public Node2D
{
public:
	TilemapRenderer();
	~TilemapRenderer() override;

	//Rewrite shader to use a image for the tilemap and a tileset
	void render() override;
	void setTilemap(Tilemap* tm);
	//Retuns the index of the tile, -1 if the position is not on the tilemap
	int worldToTile(glm::vec2 pos, bool topLeft = false);
	//returns the position of the tile using the index
	//with the position being the bottom left corner
	glm::vec2 tileToPosition(int index);
	bool isTileIndexValid(int index);
	
private:
	Tilemap* tilemap;

	static Shader* _shader;
	static bool init;

	glm::vec4 _tilesetInfo;
	glm::vec4 _tilemapInfo;

	bgfx::IndexBufferHandle _ibh;
	bgfx::VertexBufferHandle _vbh;

	//Sampler2D handle
	bgfx::UniformHandle u_tileset;
	//Sampler2D handle
	bgfx::UniformHandle u_tilemap;

	//Sprite pixel width, height, tile width, tile height
	bgfx::UniformHandle u_tilesetInfo;
	bgfx::UniformHandle u_tilemapInfo;
	
};
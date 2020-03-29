#pragma once

#include "Engine/Nodes/Node.h"

#include <vector>
#include <bgfx/bgfx.h>
#include <glm/vec2.hpp>

class Shader;
class Tilemap;

struct TilemapVertex
{
	float x;
	float y;
	float z;
	uint32_t abgr;
	int16_t m_u;
	int16_t m_v;
	static bgfx::VertexLayout pcvLayout;
	static TilemapVertex planeVerts[];
	static const uint16_t planeTriList[];
	static void init();
};


class TilemapRenderer : public Node
{
public:
	TilemapRenderer();
	~TilemapRenderer() override;

	void render();
	void setTilemap(Tilemap* tm);
	//Retuns the index of the tile, -1 if the position is not on the tilemap
	int worldToTile(glm::vec2 pos);
	//returns the position of the tile using the index
	//with the position being the bottom left corner
	glm::vec2 tileToPosition(int index);
	
private:
	Tilemap* tilemap;
	std::vector<glm::vec4> _positions;

	static Shader* _shader;
	static bool init;

	bgfx::IndexBufferHandle _ibh;
	bgfx::VertexBufferHandle _vbh;
	bgfx::UniformHandle _s_tilemap;
	bgfx::UniformHandle _u_pos;
};
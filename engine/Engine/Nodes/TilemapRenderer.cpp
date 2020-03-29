#include "TilemapRenderer.h"

#include <glm/gtc/type_ptr.hpp>

#include "Engine/Core/Context.h"
#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Shader.h"
#include "Engine/AssetManagement/Tilemap.h"
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/Utilities/Debug.h"

bgfx::VertexLayout TilemapVertex::pcvLayout;

TilemapVertex TilemapVertex::planeVerts[] = {
	{0.0f, 0.0f, 0.0f, 0xffffffff, 0, 0x7fff},
	{1.0f, 0.0f, 0.0f, 0xffffffff, 0x7fff, 0x7fff},
	{1.0f, 1.0f, 0.0f, 0xffffffff, 0x7fff, 0},
	{0.0f, 1.0f, 0.0f, 0xffffffff, 0, 0}
};
const uint16_t TilemapVertex::planeTriList[] = {
	0,1,2,
	0,2,3
};

void TilemapVertex::init()
{
	pcvLayout.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
		.end();	
}

Shader* TilemapRenderer::_shader = nullptr;
bool TilemapRenderer::init = false;


TilemapRenderer::TilemapRenderer()
{
	if (!init) {
		TilemapVertex::init();
		_shader = AssetManager::get<Shader>("assets/shaders/vs_tile.bin");
		init = true;
	}

	tilemap = nullptr;
	_s_tilemap = bgfx::createUniform("s_sprite", bgfx::UniformType::Sampler);
	_u_pos = bgfx::createUniform("u_pos", bgfx::UniformType::Vec4);
	_ibh = bgfx::createIndexBuffer(bgfx::makeRef(TilemapVertex::planeTriList, sizeof(TilemapVertex::planeTriList)));
	_vbh.idx = -1;
}

TilemapRenderer::~TilemapRenderer()
{
	bgfx::destroy(_s_tilemap);
	bgfx::destroy(_ibh);
	bgfx::destroy(_vbh);
	bgfx::destroy(_u_pos);
}


//Need to make it so the draw is one call
//This is too expensive
void TilemapRenderer::render()
{
	if (tilemap == nullptr) { return; }
	bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_BLEND_ALPHA, BGFX_STATE_BLEND_ADD);
	for (size_t i = 0; i < tilemap->size(); i++)
	{
		bgfx::setVertexBuffer(0, _vbh);
		bgfx::setIndexBuffer(_ibh);
		bgfx::setTexture(0, _s_tilemap, tilemap->getTile(i).sprite->handle);
		bgfx::setUniform(_u_pos, glm::value_ptr(_positions[i]));
		bgfx::setTransform(glm::value_ptr(transform.getGlobalMatrix()));
		bgfx::submit(0, _shader->getHandle());
	}
}

//Likely need to optomize this to not use so many verts
void TilemapRenderer::setTilemap(Tilemap* tm)
{
	//Clear VBS

	if (bgfx::isValid(_vbh)) {
		bgfx::destroy(_vbh);
	}

	tilemap = tm;
	_positions.resize(tm->size());

	TilemapVertex verts[4];
	memcpy(verts, TilemapVertex::planeVerts, sizeof(TilemapVertex::planeVerts));
	for (size_t i = 0; i < 4; i++)
	{
		verts[i].x *= tm->tileWidth;
		verts[i].y *= tm->tileHeight;
	}

	_vbh = bgfx::createVertexBuffer(bgfx::copy(verts, sizeof(TilemapVertex::planeVerts)), TilemapVertex::pcvLayout);

	for (size_t i = 0; i < tm->size(); i++)
	{
		_positions[i].x = (i % tm->getWidth()) * tm->tileWidth;
		_positions[i].y = (i / tm->getWidth()) * tm->tileHeight;
		_positions[i].x /= Context::getWindowWidth()/2;
		_positions[i].y /= Context::getWindowHeight()/2;
	}
}

int TilemapRenderer::worldToTile(glm::vec2 pos) {

	glm::vec2 renPos = transform.getPosition();
	unsigned int pixelWidth = tilemap->getWidth() * tilemap->tileWidth;
	unsigned int pixelHeiht = tilemap->getHeight() * tilemap->tileHeight;
	pixelWidth += renPos.x;
	pixelHeiht += renPos.y;

	if (pos.x > pixelWidth || pos.x < renPos.x) {
		return -1;
	}

	if (pos.y > pixelHeiht || pos.y < renPos.y) {
		return -1;
	}

	glm::vec2 relPos = pos - renPos;
	relPos.x /= tilemap->tileWidth;
	relPos.y /= tilemap->tileHeight;

	return std::floor(relPos.x) + (std::floor(relPos.y) * tilemap->getHeight());
}

glm::vec2 TilemapRenderer::tileToPosition(int index)
{
	glm::vec2 retval = transform.getPosition();
	retval.x += (index % tilemap->getWidth()) * tilemap->tileWidth;
	retval.y += (index / tilemap->getWidth()) * tilemap->tileHeight;
	return retval;
}

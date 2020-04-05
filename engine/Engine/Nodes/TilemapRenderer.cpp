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
	u_tilemap = bgfx::createUniform("u_tilemap", bgfx::UniformType::Sampler);
	u_tileset = bgfx::createUniform("u_tileset", bgfx::UniformType::Sampler);
	u_tilesetInfo = bgfx::createUniform("u_tilesetInfo", bgfx::UniformType::Vec4);
	u_tilemapInfo = bgfx::createUniform("u_tilemapInfo", bgfx::UniformType::Vec4);
	_ibh = bgfx::createIndexBuffer(bgfx::makeRef(TilemapVertex::planeTriList, sizeof(TilemapVertex::planeTriList)));
	_vbh.idx = -1;
}

TilemapRenderer::~TilemapRenderer()
{
	bgfx::destroy(u_tilemap);
	bgfx::destroy(u_tileset);

	bgfx::destroy(u_tilemapInfo);
	bgfx::destroy(u_tilesetInfo);

	bgfx::destroy(_ibh);
	bgfx::destroy(_vbh);
}


//Need to make it so the draw is one call
//This is too expensive
void TilemapRenderer::render()
{
	if (tilemap == nullptr) { return; }
	bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_BLEND_ALPHA | BGFX_STATE_DEPTH_TEST_LESS, BGFX_STATE_BLEND_ADD);
	bgfx::setVertexBuffer(0, _vbh);
	bgfx::setIndexBuffer(_ibh);
	bgfx::setTexture(0, u_tilemap, tilemap->getTilemapSprite()->handle);
	bgfx::setTexture(1, u_tileset, tilemap->getTilesetSprite()->handle);
	bgfx::setUniform(u_tilemapInfo, glm::value_ptr(_tilemapInfo));
	bgfx::setUniform(u_tilesetInfo, glm::value_ptr(_tilesetInfo));
	bgfx::setTransform(glm::value_ptr(transform.getGlobalMatrix()));
	bgfx::submit(0, _shader->getHandle());
}

//Generate one single plane
void TilemapRenderer::setTilemap(Tilemap* tm)
{
	//Clear VBS

	if (bgfx::isValid(_vbh)) {
		bgfx::destroy(_vbh);
	}

	tilemap = tm;
	TilemapVertex verts[4];
	memcpy(verts, TilemapVertex::planeVerts, sizeof(TilemapVertex::planeVerts));
	for (size_t i = 0; i < 4; i++)
	{
		verts[i].x *= tm->getPixelWidth();
		verts[i].y *= tm->getPixelHeight();
	}


	//Should modify the shader and data passed in to only what is needed. The ratio of tiles to width/length
	_tilemapInfo = { tm->getTilemapSprite()->width, tm->getTilemapSprite()->height, 1 , 1};
	_tilesetInfo = { tm->getTilesetSprite()->width, tm->getTilesetSprite()->height, tm->getTileWidth(), tm->getTileHeight() };
	Debug::Log("Tileset Pixel : " + std::to_string(_tilesetInfo.x) 
			+ " Tileset Pixel: " + std::to_string(_tilesetInfo.z) 
			+ " " +  std::to_string(_tilesetInfo.z / _tilesetInfo.x));

	_vbh = bgfx::createVertexBuffer(bgfx::copy(verts, sizeof(TilemapVertex::planeVerts)), TilemapVertex::pcvLayout);
}

int TilemapRenderer::worldToTile(glm::vec2 pos) {

	glm::vec2 renPos = transform.getPosition();
	unsigned int pixelWidth = tilemap->getPixelWidth();
	unsigned int pixelHeiht = tilemap->getPixelHeight();
	pixelWidth += renPos.x;
	pixelHeiht += renPos.y;

	if (pos.x > pixelWidth || pos.x < renPos.x) {
		return -1;
	}

	if (pos.y > pixelHeiht || pos.y < renPos.y) {
		return -1;
	}

	glm::vec2 relPos = pos - renPos;
	relPos.x /= tilemap->getTileWidth();
	relPos.y /= tilemap->getTileHeight();

	return std::floor(relPos.x) + (std::floor(relPos.y) * tilemap->getHeight());
}

glm::vec2 TilemapRenderer::tileToPosition(int index)
{
	glm::vec2 retval = transform.getPosition();
	retval.x += (index % tilemap->getWidth()) * tilemap->getTileWidth();
	retval.y += (index / tilemap->getWidth()) * tilemap->getTileHeight();
	return retval;
}

#include "TilemapRenderer.h"

#include <glm/gtc/type_ptr.hpp>

#include "Engine/Core/Context.h"
#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Shader.h"
#include "Engine/AssetManagement/Tilemap.h"
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/Utilities/Debug.h"

#include "Engine/Data/VertexTypes.h"

Shader* TilemapRenderer::_shader = nullptr;
bool TilemapRenderer::init = false;


TilemapRenderer::TilemapRenderer()
{
	if (!init) {
		me::data::PositionColorUVVertex::init();
		_shader = AssetManager::get<Shader>("assets/shaders/vs_tile.bin");
		init = true;
	}

	tilemap = nullptr;
	u_tilemap = bgfx::createUniform("u_tilemap", bgfx::UniformType::Sampler);
	u_tileset = bgfx::createUniform("u_tileset", bgfx::UniformType::Sampler);
	u_tilesetInfo = bgfx::createUniform("u_tilesetInfo", bgfx::UniformType::Vec4);
	u_tilemapInfo = bgfx::createUniform("u_tilemapInfo", bgfx::UniformType::Vec4);
	_ibh = bgfx::createIndexBuffer(bgfx::makeRef(me::data::PositionColorUVVertex::planeTriList, sizeof(me::data::PositionColorUVVertex::planeTriList)));
	_vbh.idx = BGFX_INVALID_HANDLE;
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
	me::data::PositionColorUVVertex verts[4];
	memcpy(verts, me::data::PositionColorUVVertex::planeVerts, sizeof(me::data::PositionColorUVVertex::planeVerts));
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

	_vbh = bgfx::createVertexBuffer(bgfx::copy(verts, sizeof(me::data::PositionColorUVVertex::planeVerts)), me::data::PositionColorUVVertex::layout);
}

int TilemapRenderer::worldToTile(glm::vec2 pos, bool topLeft) {

	glm::vec2 renPos = transform.getPosition();
	unsigned int pixelWidth = tilemap->getPixelWidth();
	unsigned int pixelHeiht = tilemap->getPixelHeight();
	pixelWidth += renPos.x;
	pixelHeiht += renPos.y;

	

	if (topLeft) {
		glm::vec2 posNorm = pos - renPos;
		float halfHeight = tilemap->getPixelHeight() / 2;
		if (posNorm.y > halfHeight)
		{
			posNorm.y -= (halfHeight - (tilemap->getPixelHeight() - posNorm.y)) * 2;
		}
		else {
			posNorm.y += (halfHeight - posNorm.y)*2;
		}

		pos = posNorm + renPos;
	}

	if (pos.x > pixelWidth || pos.x < renPos.x) {
		return ME_TILE_INVALID;
	}

	if (pos.y > pixelHeiht || pos.y < renPos.y) {
		return ME_TILE_INVALID;
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

bool TilemapRenderer::isTileIndexValid(int index)
{
	return (index != ME_TILE_INVALID) && (index < tilemap->size());
}

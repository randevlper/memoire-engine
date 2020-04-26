#include "SpriteRenderer.h"
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/Core/Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "Engine/AssetManagement/Shader.h"
#include "Engine/AssetManagement/AssetManager.h"

#include "Engine/Utilities/DebugMemory.h"

Shader* SpriteRenderer::shader = nullptr;
bool SpriteRenderer::init = false;
SpriteRenderer::SpriteRenderer()
{
	if (!init) {
		me::data::PositionColorUVVertex::init();
		shader = AssetManager::get<Shader>("assets/shaders/vs_sprite.bin");
		//FileUtility::loadProgram("assets/shaders/vs_sprite.bin","assets/shaders/fs_sprite.bin");
		init = true;
	}

	vbh = bgfx::createVertexBuffer(bgfx::makeRef(me::data::PositionColorUVVertex::planeVerts, sizeof(me::data::PositionColorUVVertex::planeVerts)), me::data::PositionColorUVVertex::pcvLayout);
	ibh = bgfx::createIndexBuffer(bgfx::makeRef(me::data::PositionColorUVVertex::planeTriList, sizeof(me::data::PositionColorUVVertex::planeTriList)));
	s_sprite = bgfx::createUniform("s_sprite", bgfx::UniformType::Sampler);
	_sprite = nullptr;
}

SpriteRenderer::~SpriteRenderer()
{
	bgfx::destroy(vbh);
	bgfx::destroy(ibh);
	bgfx::destroy(s_sprite);
}

void SpriteRenderer::setSprite(Sprite* sprite)
{
	if (sprite == nullptr) { return; }
	bgfx::destroy(vbh);

	float w = (sprite->width)/2;
	float h = (sprite->height)/2;

	memcpy(newVerts, me::data::PositionColorUVVertex::planeVerts, 
		sizeof(me::data::PositionColorUVVertex::planeVerts));
	newVerts[0].xy({ -w,-h });
	newVerts[1].xy({ w,-h });
	newVerts[2].xy({ w,h });
	newVerts[3].xy({-w, h});

	vbh = bgfx::createVertexBuffer(bgfx::makeRef(newVerts, sizeof(newVerts)), me::data::PositionColorUVVertex::pcvLayout);

	_sprite = sprite;
}

Sprite* SpriteRenderer::getSprite()
{
	return _sprite;
}

void SpriteRenderer::render()
{
	if (_sprite == nullptr) { return; }
	bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_BLEND_ALPHA, BGFX_STATE_BLEND_ADD);
	bgfx::setTransform(glm::value_ptr(transform.getGlobalMatrix()));
	bgfx::setVertexBuffer(0, vbh);
	bgfx::setIndexBuffer(ibh);

	if (bgfx::isValid(_sprite->handle)) {
		bgfx::setTexture(0, s_sprite, _sprite->handle);
	}
	//bgfx::setUniform(s_world, glm::value_ptr(transform.getGlobalMatrix()));
	

	bgfx::submit(0, shader->getHandle());
}

void SpriteRenderer::destroy()
{
}

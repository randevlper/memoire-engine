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
bool SpriteRenderer::isInit = false;
SpriteRenderer::SpriteRenderer()
{
	_type = "SpriteRenderer";
	if (!isInit) {
		me::data::PositionColorUVVertex::init();
		shader = AssetManager::get<Shader>("assets/shaders/vs_sprite.bin");
		//FileUtility::loadProgram("assets/shaders/vs_sprite.bin","assets/shaders/fs_sprite.bin");
		isInit = true;
	}

	vbh = bgfx::createVertexBuffer(bgfx::makeRef(me::data::PositionColorUVVertex::verts, sizeof(me::data::PositionColorUVVertex::verts)), me::data::PositionColorUVVertex::layout);
	ibh = bgfx::createIndexBuffer(bgfx::makeRef(me::data::PositionColorUVVertex::indices, sizeof(me::data::PositionColorUVVertex::indices)));
	s_sprite = bgfx::createUniform("s_sprite", bgfx::UniformType::Sampler);
	u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);
	_sprite = nullptr;
	_color = { 1,1,1,1 };
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

	memcpy(newVerts, me::data::PositionColorUVVertex::verts, 
		sizeof(me::data::PositionColorUVVertex::verts));
	newVerts[0].xy({ -w,-h });
	newVerts[1].xy({ w,-h });
	newVerts[2].xy({ w,h });
	newVerts[3].xy({-w, h});

	vbh = bgfx::createVertexBuffer(bgfx::makeRef(newVerts, sizeof(newVerts)), me::data::PositionColorUVVertex::layout);

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
	Transform t = _transform;
	glm::mat4x4 m = t.getGlobalMatrix();
	bgfx::setTransform(glm::value_ptr(m));
	bgfx::setVertexBuffer(0, vbh);
	bgfx::setIndexBuffer(ibh);
	bgfx::setUniform(u_color, &_color);

	if (bgfx::isValid(_sprite->handle)) {
		bgfx::setTexture(0, s_sprite, _sprite->handle);
	}
	//bgfx::setUniform(s_world, glm::value_ptr(transform.getGlobalMatrix()));
	

	bgfx::submit(0, shader->getHandle(), sort);
}

void SpriteRenderer::destroy()
{
}

nlohmann::json SpriteRenderer::to_json()
{
	nlohmann::json j = Node2D::to_json();
	j["type"] = "SpriteRenderer";
	j["sprite"] = _sprite->to_json();
	j["color"] = _color;
	//Sprite location
	return j;
}

void SpriteRenderer::from_json(const nlohmann::json& j)
{
	Node2D::from_json(j);
	setSprite(AssetManager::get_json<Sprite>(j["sprite"]));
	_color = j["color"];
}

glm::vec4 SpriteRenderer::getColor()
{
	return _color;
}

//Expects values from 0-1
void SpriteRenderer::setColor(glm::vec4 value)
{
	_color = value;
}

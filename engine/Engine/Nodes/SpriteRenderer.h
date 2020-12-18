#pragma once
#include "Engine/Nodes/Node2D.h"
#include <bgfx/bgfx.h>

#include "Engine/Data/VertexTypes.h"

class Sprite;
class Shader;

class SpriteRenderer : public Node2D
{
public:
	SpriteRenderer();
	~SpriteRenderer() override;

	void setSprite(Sprite* sprite);
	Sprite* getSprite();
	void render() override;
	static void destroy();

	nlohmann::json to_json() override;
	void from_json(const nlohmann::json& j) override;

private:
	Sprite* _sprite;
	me::data::PositionColorUVVertex newVerts[4];
	bgfx::VertexBufferHandle vbh;
	bgfx::IndexBufferHandle ibh;
	bgfx::UniformHandle s_sprite;

	static Shader* shader;
	static bool init;
};
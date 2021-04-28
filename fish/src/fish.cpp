#include "fish.h"

#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/AssetManagement/Sprite.h"

Fish::Fish()
{
	_type = "Fish";
	_score = 10;
	_speed = 300;
	_spriteRenderer = nullptr;
}

void Fish::init()
{
	std::vector<Node2D*> children = getTransform().getChildren();
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i]->getType() == "SpriteRenderer") {
			_spriteRenderer = dynamic_cast<SpriteRenderer*>(children[i]);
			break;
		}
	}

	if (_spriteRenderer == nullptr) {
		World* world = me::WorldManager::getWorld();
		_spriteRenderer = world->create<SpriteRenderer>();
		_spriteRenderer->setSprite(AssetManager::get<Sprite>("assets/ui/box.png"));
		Transform t = _spriteRenderer->getTransform();
		t.setParent(this);
		_spriteRenderer->setTransform(t);
	}
}

void Fish::destroy()
{
	Body2D::destroy();
	World* world = me::WorldManager::getWorld();
	world->destroy(_spriteRenderer);
}

void Fish::from_json(const nlohmann::json& j)
{
	Body2D::from_json(j);
	_speed = j["speed"];
	_score = j["score"];
}

nlohmann::json Fish::to_json()
{
	nlohmann::json j = Body2D::to_json();
	j["speed"] = _speed;
	j["score"] = _score;
	return j;
}

SpriteRenderer* Fish::getSpriteRenderer()
{
	return _spriteRenderer;
}

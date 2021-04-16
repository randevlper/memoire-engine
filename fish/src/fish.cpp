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
	_speed = 5;
}

void Fish::init()
{
	World* world = me::WorldManager::getWorld();
	_spriteRenderer = world->create<SpriteRenderer>();
	_spriteRenderer->setSprite(AssetManager::get<Sprite>("assets/ui/box.png"));
	Transform t = _spriteRenderer->getTransform();
	t.setParent(this);
	_spriteRenderer->setTransform(t);
}

void Fish::destroy()
{
	World* world = me::WorldManager::getWorld();
	world->destroy(_spriteRenderer);
}

SpriteRenderer* Fish::getSpriteRenderer()
{
	return _spriteRenderer;
}

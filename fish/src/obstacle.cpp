#include "obstacle.h"

#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/Core/World.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Sprite.h"

#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

#include "collision.h"
#include "hook.h"

Obstacle::Obstacle()
{
	_type = "Obstacle";
	setupBox(0, 0, 100, 100, Body2DType::Dynamic, CollisionCatagories::FISH, CollisionCatagories::HOOK | CollisionCatagories::BOUNDARY);
}

void Obstacle::init()
{
	World* world = me::WorldManager::getWorld();
	_spriteRenderer = world->create<SpriteRenderer>();
	Transform t = _spriteRenderer->getTransform();
	t.setParent(this);
	_spriteRenderer->setTransform(t);
	_spriteRenderer->setSprite(AssetManager::get<Sprite>("assets/sprites/debrie.png"));
}

void Obstacle::destroy()
{
	Body2D::destroy();
	World* world = me::WorldManager::getWorld();
	world->destroy(_spriteRenderer);
}

void Obstacle::OnContactStart(Collision2D collision)
{
	if (collision.other != nullptr) {
		if(collision.other->getType() == "Hook"){
			Hook* hook = dynamic_cast<Hook*>(collision.other);
			hook->loseFish();
		}
	}
}
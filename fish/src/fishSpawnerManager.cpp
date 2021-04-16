#include "fishSpawnerManager.h"

#include "Engine/Core/Context.h"
#include "Engine/Core/World.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Sprite.h"

#include "Engine/Utilities/Debug.h"

#include "Engine/Nodes/SpriteRenderer.h"

#include "fish.h"
#include "fishSpawner.h"
#include "collision.h"

FishSpawnerManager::FishSpawnerManager()
{
	_type = "FishSpawnerManager";
	_fishSpawners = std::vector<FishSpawner*>();
	_timer = 0;
	_time = 5;
}


void FishSpawnerManager::init()
{
	World* world = me::WorldManager::getWorld();
	const std::vector<Node*> nodes = world->getNodes();
	
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->getType() == "FishSpawner") {
			FishSpawner* fishSpawner = dynamic_cast<FishSpawner*>(nodes[i]);
			_fishSpawners.push_back(fishSpawner);
		}
	}

}

void FishSpawnerManager::tick()
{
	_timer += Context::getDeltaTime();
	if (_timer >= _time) {
		World* world = me::WorldManager::getWorld();
		for (size_t i = 0; i < _fishSpawners.size(); i++)
		{
			Fish* fish = world->create<Fish>();
			fish->getSpriteRenderer()->setSprite(AssetManager::get<Sprite>("assets/sprites/fishtest.png"));
			fish->setupBox(0, 0, 10, 10, Body2DType::Dynamic, CollisionCatagories::FISH,
				CollisionCatagories::BOUNDARY | CollisionCatagories::HOOK);
			_fishSpawners[i]->spawn(fish);
		}
		_timer = 0;
	}

}

void FishSpawnerManager::from_json(const nlohmann::json& j)
{
	Node::from_json(j);
}

nlohmann::json FishSpawnerManager::to_json()
{
	return Node::to_json();
}

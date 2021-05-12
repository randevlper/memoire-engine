#include "fishSpawnerManager.h"

#include "Engine/Core/Context.h"
#include "Engine/Core/World.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Sprite.h"

#include "Engine/Utilities/Debug.h"

#include "Engine/Nodes/SpriteRenderer.h"

#include "fish.h"
#include "fishData.h"
#include "fishSpawner.h"
#include "collision.h"
#include "obstacle.h"

struct SpawnData
{
	std::string type;
	unsigned int chance;
	FishData fishData;
};

FishSpawnerManager::FishSpawnerManager()
{
	_type = "FishSpawnerManager";
	_fishSpawners = std::vector<FishSpawner*>();
	_timer = 0;
	_time = 1;

	_gen = std::mt19937(_rand());

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


	_distribution = std::uniform_int_distribution<>(0, _fishSpawners.size() - 1);

	std::vector<FishData> fishData = {
	{10, 300, "assets/sprites/fishtest.png", SDL_Scancode::SDL_SCANCODE_RIGHT, "assets/sprites/arrowright.png"},
	{10, 250, "assets/sprites/fishtestb.png", SDL_Scancode::SDL_SCANCODE_LEFT, "assets/sprites/arrowleft.png"},
	{10, 200, "assets/sprites/fishtestwhale.png", SDL_Scancode::SDL_SCANCODE_DOWN, "assets/sprites/arrowdown.png"}
	};
	
	std::vector<SpawnData> spawnData = {
		{"Fish", 50, fishData[0]},
		{"Fish", 25, fishData[1]},
		{"Fish", 10, fishData[2]},
		{"Obstacle", 15, {}},
	};

	setSpawnData(spawnData);
}

void FishSpawnerManager::tick()
{
	_timer += Context::getDeltaTime();
	if (_timer >= _time) {
		World* world = me::WorldManager::getWorld();
		//Debug::Log("Spawn: " + std::to_string(spawn));
		int fishSpawner = _distribution(_gen);
		unsigned int spawn = _spawnDist(_gen);

		unsigned int spawnLast = 0;
		unsigned int spawnTotal = 0;

		for (size_t i = 0; i < _spawnData.size(); i++)
		{
			spawnTotal += _spawnData[i].chance;
			if (spawn > spawnLast && spawn < spawnTotal) {
				if (_spawnData[i].type == "Fish") {
					Fish* fish = world->create<Fish>();
					fish->setFishData(_spawnData[i].fishData);
					fish->setupBox(0, 0, 10, 10, Body2DType::Dynamic, CollisionCatagories::FISH,
						CollisionCatagories::BOUNDARY | CollisionCatagories::HOOK);
					_fishSpawners[fishSpawner]->spawn(fish, fish->getSpeed());
				}

				if (_spawnData[i].type == "Obstacle") {
					Obstacle* obstacle = world->create<Obstacle>();
					_fishSpawners[fishSpawner]->spawn(obstacle, 200);
				}
			}

			spawnLast += _spawnData[i].chance;
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

void FishSpawnerManager::setSpawnData(std::vector<SpawnData> value)
{
	_spawnData = value;
	_spawnDist = std::uniform_int_distribution<>(0, 100);
}

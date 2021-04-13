#include "fishSpawner.h"

#include <random>
#include <string>
#include <SDL_timer.h>

#include "fish.h"
#include "collision.h"

#include "Engine/Core/Context.h"
#include "Engine/Physics2D/Body2D.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

FishSpawner::FishSpawner()
{
	_type = "FishSpawner";
	_timer = 0;
	_time = 1.0f;
	_spawnDir = 1;
	_speed = 10;
}

void FishSpawner::init() {
	_world = me::WorldManager::getWorld();
}

void FishSpawner::tick()
{
	_timer += Context::getDeltaTime();

	if (_timer >= _time) {
		Fish* fish = _world->create<Fish>();
		glm::vec2 pos = getTransform().getPosition();
		fish->setupBox(pos.x, pos.y, 10, 10, Body2DType::Dynamic, CollisionCatagories::FISH,
			CollisionCatagories::BOUNDARY | CollisionCatagories::HOOK);
		fish->setVelocity({ _spawnDir * _speed, 0 });
		_timer = 0;
	}

}

nlohmann::json FishSpawner::to_json()
{
	nlohmann::json j = Node2D::to_json();
	j["spawnDir"] = _spawnDir;
	j["speed"] = _speed;
	j["time"] = _time;
	return j;
}

void FishSpawner::from_json(const nlohmann::json& j)
{
	Node2D::from_json(j);
	_spawnDir = j["spawnDir"];
	_speed = j["speed"];
	_time = j["time"];
}

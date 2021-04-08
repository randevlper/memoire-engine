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
}

void FishSpawner::init() {
	_world = me::WorldManager::getWorld();
}

void FishSpawner::tick()
{
	Fish* fish = _world->create<Fish>();
	glm::vec2 pos = getTransform().getPosition();
	fish->setupBox(pos.x, pos.y, 10, 10, Body2DType::Dynamic, CollisionCatagories::FISH,
		CollisionCatagories::BOUNDARY | CollisionCatagories::HOOK);
	fish->setVelocity({ 10, 0});
}

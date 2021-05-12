#include "fishSpawner.h"

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
	_spawnDir = 1;
}

void FishSpawner::spawn(Body2D* body, float speed)
{
	Transform t = body->getTransform();
	t.setLocalScale({ _spawnDir,1 });
	body->setTransform(t);
	body->setPosition(getTransform().getPosition());
	body->setVelocity({ _spawnDir * speed, 0 });
}

nlohmann::json FishSpawner::to_json()
{
	nlohmann::json j = Node2D::to_json();
	j["spawnDir"] = _spawnDir;
	return j;
}

void FishSpawner::from_json(const nlohmann::json& j)
{
	Node2D::from_json(j);
	_spawnDir = j["spawnDir"];
}

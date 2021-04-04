#pragma once
#include "Engine/Nodes/Node2D.h"
class World;

class FishSpawner : public Node2D
{
public:
	FishSpawner();
	~FishSpawner();

	void tick(float deltaTime);
	float spawnTime = 0;

private:
	float _timer;

	World* _world;
};
#pragma once
#include "Engine/Nodes/Node2D.h"
class World;

class FishSpawner : public Node2D
{
public:
	FishSpawner();

	void tick(float deltaTime);

private:

	World* _world;
};
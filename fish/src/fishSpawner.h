#pragma once
#include "Engine/Nodes/Node2D.h"
class World;

class FishSpawner : public Node2D
{
public:
	FishSpawner();

	void init() override;
	void tick() override;

private:

	World* _world;
};
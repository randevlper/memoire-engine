#pragma once
#include "Engine\Nodes\Node.h"
#include <vector>

class World
{
public:
	World();
	~World();

	//Raycast
	//AABB Query
	//Node Creation
	
	//void tick();

private:
	//Contain Nodes
	Node* _root;
};
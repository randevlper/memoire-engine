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
	//void AddNode(Node* node);
	//void RemoveNode(Node* node);
	//void tick(float delta);

private:
	//Contain Nodes
	Node* _root;
};
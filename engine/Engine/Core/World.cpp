#include "World.h"

#include "Engine/Nodes/Body.h"
#include "Engine/Utilities/DebugMemory.h"

World::World()
{
	_root = DBG_NEW Node2D();
	_nodes = std::vector<Node*>();
}

World::~World()
{
	for (size_t i = 0; i < _nodes.size(); i++)
	{
		if (_nodes[i] != nullptr) {
			delete(_nodes[i]);
		}
	}
	delete(_root);
}

void World::tick(float delta)
{

}

void World::render()
{

}

#include "World.h"

#include <Box2D/Box2D.h>


#include "Engine/Nodes/Body.h"
#include "Engine/Utilities/DebugMemory.h"

World::World()
{
	_root = DBG_NEW Node2D();
	_world = DBG_NEW b2World({0,-9.8});
	_nodes = std::vector<Node2D*>();
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
	delete(_world);
}

void World::tick(float delta)
{

}

Body* World::CreateBody(BodyDef& def) {
	return nullptr;
}

void World::setGravity(glm::vec2& value)
{
}

glm::vec2 World::getGravity()
{
	//TODO Custom Type Conversion
	return {_world->GetGravity().x, _world->GetGravity().y};
}

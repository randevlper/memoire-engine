#include "World.h"

#include "Engine/Nodes/Body.h"
#include "Engine/Utilities/DebugMemory.h"
#include "Engine/Utilities/ObjectFactory.h"
#include "Engine/Utilities/Debug.h"

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
	for (size_t i = 0; i < _nodes.size(); i++)
	{
		_nodes[i]->render();
	}
}

nlohmann::json World::to_json()
{
	nlohmann::json retval;
	for (size_t i = 0; i < _nodes.size(); i++)
	{
		retval["nodes"][i] = (_nodes[i]->to_json());
	}
	return retval;
}

void World::from_json(const nlohmann::json& j)
{
	Node* node;
	for (auto& [key, value] : j["nodes"].items()) {
		node = me::util::ObjectFactory::createObject(value["type"]);
		if (node == nullptr) {
			Debug::Log("Failed to create. Type not found! " + value["type"]);
		}
		else {
			node->from_json(value);
			_nodes.push_back(node);
		}
	}
}

#pragma once
#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include "Engine\Nodes\Node.h"
#include "Engine\Nodes\Node2D.h"
#include "Engine\UI\NodeUI.h"

#define WORLD_FILE_TYPE ".world"

class World
{
public:
	World();
	~World();

	//Raycast
	//AABB Query
	//Node Creation
	void tick(float delta);
	void render();

	const std::vector<Node*>& getNodes() {
		return _nodes;
	}

	void setNodes(std::vector<Node*> nodes) {
		_nodes = nodes;
	}

	//Create node <Templated>
	template<class nodeclass>
	nodeclass* create();
	Node* create(std::string nodeType);

	bool destroy(std::string name);
	bool destroy(Node* node);

	template<class T>
	T* get(std::string name);

	//Delete a node by refrence
	//bool destroy(Node* node);
	//Delete a node by name
	//bool destroy(std::string name);

	std::string name;

	nlohmann::json to_json();
	void from_json(const nlohmann::json& j);

private:
	//Contain Nodes
	Node* _root;
	std::vector<Node*> _nodes;
	//For now use a list of nodes
	//Ideally better to use a hierarchy? A node knows its children.
	bool eraseNode(Node* node, int index);
};

template<class nodeclass>
inline nodeclass* World::create()
{
	static_assert(std::is_base_of<Node, nodeclass>::value, "Nodeclass not derived from Node");
	//static_assert(std::is_base_of<NodeUI, nodeclass>::value, "Nodeclass not derived from NodeUI");
	nodeclass* node = new nodeclass();
	node->setName("node_" + std::to_string(_nodes.size()));
	_nodes.push_back(node);
	return node;
}

template<class T>
inline T* World::get(std::string name)
{
	static_assert(std::is_base_of<Node, T>::value, "T not derived from Node");
	for (size_t i = 0; i < _nodes.size(); i++)
	{
		if (_nodes[i]->getName() == name) {
			//Error checking here?
			return dynamic_cast<T*>(_nodes[i]);
		}
	}
	return nullptr;
}

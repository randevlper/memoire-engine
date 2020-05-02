#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "Engine\Nodes\Node.h"
#include "Engine\Nodes\Node2D.h"
#include "Engine\UI\NodeUI.h"

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

	//Create node <Templated>
	template<class nodeclass>
	nodeclass* create();


private:
	//Contain Nodes
	Node* _root;
	std::vector<Node*> _nodes;
	//For now use a list of nodes
	//Ideally better to use a hierarchy? A node knows its children.
};

template<class nodeclass>
inline nodeclass* World::create()
{
	static_assert(std::is_base_of<Node, nodeclass>::value, "Nodeclass not derived from Node");
	//static_assert(std::is_base_of<NodeUI, nodeclass>::value, "Nodeclass not derived from NodeUI");
	nodeclass* node = new nodeclass();
	_nodes.push_back(node);
	return node;
}

#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "Engine\Nodes\Node.h"
//#include "Box2D/Box2D.h"

class b2World;
class Body;
struct BodyDef;
class Node2D;

class World
{
public:
	World();
	~World();

	//Raycast
	//AABB Query
	//Node Creation
	void tick(float delta);
	Body* CreateBody(BodyDef& def);

	void setGravity(glm::vec2& value);
	glm::vec2 getGravity();


	//Create node <Templated>
	template<class nodeclass>
	nodeclass* create();


private:
	//Contain Nodes
	Node2D* _root;
	b2World* _world;
	glm::vec2 _gravity;

	std::vector<Node2D*> _nodes;
	//For now use a list of nodes
	//Ideally better to use a hierarchy? A node knows its children.
};

template<class nodeclass>
inline nodeclass* World::create()
{
	static_assert(std::is_base_of<Node2D, nodeclass>::value, "Nodeclass not derived from Node2D");
	nodeclass* node = new nodeclass();
	_nodes.push_back(node);
	return node;
}

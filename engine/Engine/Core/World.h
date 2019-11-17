#pragma once
#include "glm/vec2.hpp"
//#include "Box2D/Box2D.h"

class b2World;
class Body;
struct BodyDef;
class Node;

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
	void tick(float delta);
	Body* CreateBody(BodyDef& def);

	void setGravity(glm::vec2& value);
	glm::vec2 getGravity();

private:
	//Contain Nodes
	Node* _root;
	b2World* _world;
	glm::vec2 _gravity;

};
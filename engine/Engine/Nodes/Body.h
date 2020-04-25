#pragma once
#include "Node.h"
#include "glm/glm.hpp"
class b2Body;

struct BodyDef
{
	glm::vec2 position;
	glm::vec2 size;
	int friction;
	int restitution;
	int density;
};

class Body : public Node2D
{
public:
	Body(BodyDef def);
	~Body();

	//isTrigger
	//OnEnter
	//OnStay
	//OnExit

private:
	b2Body* _body;
};
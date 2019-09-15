#pragma once 
#include "Engine/Nodes/Node.h"
#include "Engine/Core/Physics.h"
#include "glm/vec2.hpp"
#include <vector>

#define COLLIDER_MAX_POINTS 32

class Collider : public Node
{
public:
	//default is a 10,10 cube
	Collider();
	Collider(std::vector<glm::vec2> &p);
	~Collider();

	//lines
	//affecting transform
	std::vector<glm::vec2> points;
	std::vector<glm::vec2> axes;

private:
	void CreateAxes();
	static glm::vec2 perp(glm::vec2& v);
};
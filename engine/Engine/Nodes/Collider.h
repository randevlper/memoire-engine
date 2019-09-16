#pragma once 
#include "Engine/Nodes/Node.h"
#include "Engine/Core/Physics.h"
#include "glm/vec2.hpp"
#include <vector>

#define COLLIDER_MAX_POINTS 32

struct AxialExtents { float min, max; };

struct Collision
{
	//Multiply all by each other and add to the position of the GameObject that
	//you do not want to collide with.
	float penetration;
	glm::vec2 collisionNormal;
	//float handedness;
};

struct SATGeometry {
	std::vector<glm::vec2> points;
	std::vector<glm::vec2> axes;
};

class Collider : public Node
{
public:
	//default is a 10,10 cube
	Collider();
	Collider(std::vector<glm::vec2> &p);
	~Collider();

	//lines
	//affecting transform
	SATGeometry geo;
	bool isStatic;

	SATGeometry Collider::getWorldGeo();
	Collision doesCollide(Collider* other);
private:
	static Collision doesCollide(SATGeometry* A, SATGeometry* B);
	static void CreateAxes(SATGeometry &g);
	static glm::vec2 perp(glm::vec2& v);
	static AxialExtents evalAxialExtents(glm::vec2& axis, std::vector<glm::vec2> &points);
};
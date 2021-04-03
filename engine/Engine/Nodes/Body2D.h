#pragma once
#include "Node2D.h"

class b2Body;

enum class Body2DType
{
	Static = 0,
	Kinematic = 1,
	Dynamic = 2
};

class Body2D : public Node2D
{
public:
	Body2D();
	~Body2D() override;

	void setupBox(int x, int y, int width, int height, Body2DType type, bool isSensor = false);
	void setPosition(glm::vec2 pos);
	glm::vec2 getPosition();

private:
	Transform transform;
	//getting transform stuff should be from this
	//For now special functions?
	b2Body* _body;
};
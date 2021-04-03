#pragma once
#include "Node2D.h"
#include "box2d/b2_types.h"

class b2Body;
class b2Contact;

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

	void setupBox(int x, int y, int width, int height, Body2DType bodyType,
		uint16 category, uint16 mask, bool isSensor = false);
	void setPosition(glm::vec2 pos);
	glm::vec2 getPosition();
	
	void setIsAwake(bool value);
	bool isAwake();

	void setIsEnabled(bool value);
	bool isEnabled();

	Body2DType getBodyType();
	bool isSensor();

	virtual void OnContactStart(b2Contact* contact, Body2D* bodyA, Body2D* bodyB);
	virtual void OnContactEnd(b2Contact* contact, Body2D* bodyA, Body2D* bodyB);

private:
	Transform transform;
	//getting transform stuff should be from this
	//For now special functions?
	b2Body* _body;
};
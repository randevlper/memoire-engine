#pragma once
#include "glm/vec2.hpp"
#include "glm/mat3x3.hpp"
class Node2D;

struct Transform
{
public:
	Transform();
	~Transform();

	glm::vec2 getLocalPosition();
	void setLocalPosition(glm::vec2 value);

	glm::vec2 getPosition();

	glm::vec2 getLocalScale();
	void setLocalScale(glm::vec2 value);

	float getLocalAngle();
	void setLocalAngle(float value);

	Node2D* getParent();
	void setParent(Node2D* value);

	void translate(glm::vec2 value);

	glm::mat4x4 getLocalMatrix();
	glm::mat4x4 getGlobalMatrix();
	float depth;
private:
	glm::vec2 _position;
	glm::vec2 _scale;
	
	float _angle;
	Node2D* _parent;
};
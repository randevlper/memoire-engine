#include "Transform.h"
#include "Engine/Nodes/Node.h"
#include "glm/gtx/matrix_transform_2d.hpp"

Transform::Transform()
{
	_position = { 0,0 };
	_scale = { 1,1 };
	_angle = 0;
	_parent = nullptr;
}

Transform::~Transform()
{

}

glm::vec2 Transform::getLocalPosition()
{
	return _position;
}

void Transform::setLocalPosition(glm::vec2 value)
{
	_position = value;
}

glm::vec2 Transform::getPosition()
{
	glm::mat3x3 m = getGlobalMatrix();
	glm::vec2 pos = { m[2].x,m[2].y };
	return pos;
}

glm::vec2 Transform::getLocalScale()
{
	return _scale;
}

void Transform::setLocalScale(glm::vec2 value)
{
	_scale = value;
}

float Transform::getLocalAngle()
{
	return _angle;
}

void Transform::setLocalAngle(float value)
{
	_angle = value;
}

Node* Transform::getParent()
{
	return _parent;
}

void Transform::setParent(Node* value)
{
	_parent = value;
}

void Transform::translate(glm::vec2 value)
{
	_position += value;
}

glm::mat3x3 Transform::getLocalMatrix()
{
	glm::mat3x3 retval = glm::mat3x3::mat(1.0f); 
	retval = glm::translate(retval, _position);
	retval = glm::scale(retval, _scale);
	retval = glm::rotate(retval, _angle);
	return  retval;
}

glm::mat3x3 Transform::getGlobalMatrix()
{
	if (_parent != nullptr) {
		return _parent->transform.getGlobalMatrix() * getLocalMatrix();
	} else {
		return getLocalMatrix();
	}
}

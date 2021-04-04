#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

#include "Engine/Nodes/Node.h"
#include "Engine/Utilities/glmJson.h"

Transform::Transform()
{
	_position = { 0,0 };
	_scale = { 1,1 };
	_angle = 0;
	_parent = nullptr;
	_parentNode = nullptr;
	depth = 0;
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
	glm::mat4x4 m = getGlobalMatrix();
	glm::vec2 pos = { m[3].x,m[3].y };
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

Transform* Transform::getParent()
{
	return _parent;
}

void Transform::setParent(Transform* value)
{
	_parent = value;
}

void Transform::translate(glm::vec2 value)
{
	_position += value;
}

glm::mat4x4 Transform::getLocalMatrix()
{
	glm::mat4x4 retval = glm::mat4x4::mat(1.0f);
	retval = glm::translate(retval, glm::vec3(_position, 1.0f));
	retval = glm::scale(retval, glm::vec3(_scale,depth));
	retval = glm::rotate(retval, _angle, glm::vec3(0, 0, 1));
	return  retval;
}

glm::mat4x4 Transform::getGlobalMatrix()
{
	if (_parent != nullptr) {
		return _parent->getGlobalMatrix() * getLocalMatrix();
	} else {
		return getLocalMatrix();
	}
}

nlohmann::json Transform::get_json()
{
	nlohmann::json j;
	j["position"] = _position;
	j["scale"] = _scale;
	j["angle"] = _angle;

	//TODO
	if (_parent != nullptr) {
		//j["parent"] = _parent->_parentNode->getName();
	}
	else {
		j["parent"] = "null";
	}
	//TODO Parent somehow
	return j;
}

void Transform::from_json(const nlohmann::json& j)
{
	setLocalPosition(j["position"]);
	setLocalScale(j["scale"]);
	setLocalAngle(j["angle"]);
}



#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

#include "Engine/Nodes/Node2D.h"
#include "Engine/Utilities/glmJson.h"

#include "Engine/Utilities/Debug.h"

Transform::Transform()
{
	_position = { 0,0 };
	_scale = { 1,1 };
	_angle = 0;
	_parent = nullptr;
	_node = nullptr;
	depth = 0;
	_children = std::vector<Node2D*>();
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

void Transform::setPosition(glm::vec2 value)
{
	//Get global transform then do the reverse to get the new local
	glm::vec2 pos = value;

	std::vector<Node2D*> nodes;
	Node2D* node = _parent;
	while (node != nullptr) {
		nodes.push_back(node);
		node = node->getTransform().getParent();
	}

	for (size_t i = 0; i < nodes.size(); i++)
	{
		pos -= nodes[i]->getTransform().getPosition();
	}
	setLocalPosition(pos);
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

Node2D* Transform::getParent()
{
	return _parent;
}

void Transform::setParent(Node2D* value)
{
	if (value != nullptr) {
		//If THIS node has a parent remove THIS node
		//glm::vec2 pos = getPosition();
		setParent(nullptr);
		
		Transform t = value ->getTransform();
		
		//Set the parent and assign this as its child
		_parent = value;
		t._children.push_back(_node);
		_parent->setTransform(t);
		//setPosition(pos);
	}
	else {
		if (_parent != nullptr) {
			//glm::vec2 pos = getPosition();
			Transform t = _parent->getTransform();
			t.removeChild(_node);
			_parent->setTransform(t);
			//setPosition(pos);
		}
		_parent = nullptr;
	}
}

std::vector<Node2D*> Transform::getChildren()
{
	return _children;
}


void Transform::removeChild(Node2D* value)
{
	for (int i = 0; i < _children.size(); i++)
	{
		if (_children[i] == value) {
			_children.erase(_children.begin() + i);
			break;
		}
	}
}


void Transform::setNode2D(Node2D* value)
{
	_node = value;
}

Node2D* Transform::getNode2D()
{
	return _node;
}

void Transform::translate(glm::vec2 value)
{
	_position += value;
}

glm::mat4x4 Transform::getLocalMatrix()
{
	glm::mat4x4 retval = glm::mat4x4::mat(1.0f);
	retval = glm::translate(retval, glm::vec3(_position, 1.0f));
	retval = glm::scale(retval, glm::vec3(_scale, depth));
	retval = glm::rotate(retval, _angle, glm::vec3(0, 0, 1));
	return  retval;
}

glm::mat4x4 Transform::getGlobalMatrix()
{
	if (_parent != nullptr) {
		return _parent->getTransform().getGlobalMatrix() * getLocalMatrix();
	}
	else {
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
		j["parent"] = _parent->getName();
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


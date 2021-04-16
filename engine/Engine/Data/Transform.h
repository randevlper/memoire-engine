#pragma once
#include "glm/fwd.hpp"
#include <nlohmann/json.hpp>
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


	//Node transform and a normal transform for math?
	Node2D* getParent();
	//Use this
	void setParent(Node2D* value);

	//Multiple childs eventually
	Node2D* getChild();

	void setNode2D(Node2D* value);
	Node2D* getNode2D();


	//void addChild(Transform* child);
	//void removeChild(Transform* child);

	void translate(glm::vec2 value);

	glm::mat4x4 getLocalMatrix();
	glm::mat4x4 getGlobalMatrix();
	float depth;

	nlohmann::json get_json();
	void from_json(const nlohmann::json& j);


private:
	glm::vec2 _position;
	glm::vec2 _scale;
	
	float _angle;

	Node2D* _parent;
	Node2D* _child;

	Node2D* _node;
};
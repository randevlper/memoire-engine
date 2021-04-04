#pragma once
#include "Node.h"
#include "Engine/Data/Transform.h"

class Node2D : public Node
{
public:
	Node2D();
	~Node2D() override;
	Transform transform;

	virtual nlohmann::json to_json() override{
		nlohmann::json j = Node::to_json();
		j["transform"] = transform.get_json();
		return j;
	}

	virtual void from_json(const nlohmann::json& j) override {
		Node::from_json(j);
		transform.from_json(j["transform"]);
	}

private:
};
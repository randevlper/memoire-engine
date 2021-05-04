#pragma once
#include "Engine/Nodes/Node.h"
#include "Engine/Data/RectTransform.h"

class NodeUI : public Node
{
public:
	NodeUI();
	virtual ~NodeUI();
	RectTransform rectTransform;

	virtual nlohmann::json to_json() override{
		nlohmann::json j = Node::to_json();
		j["rectTransform"] = rectTransform.get_json();
		return j;
	}

	virtual void from_json(const nlohmann::json& j)  override {
		Node::from_json(j);
		rectTransform.from_json(j["rectTransform"]);
	}

private:

};
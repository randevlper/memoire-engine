#pragma once
#include "Engine/Nodes/Node.h"
#include "Engine/Data/RectTransform.h"

class NodeUI : public Node
{
public:
	NodeUI();
	virtual ~NodeUI();
	
	RectTransform getRectTransform() {
		return _rectTransform;
	}
	void setRectTransform(RectTransform value) {
		_rectTransform = value;
	}


	virtual nlohmann::json to_json() override{
		nlohmann::json j = Node::to_json();
		j["rectTransform"] = _rectTransform.get_json();
		return j;
	}

	virtual void from_json(const nlohmann::json& j)  override {
		Node::from_json(j);
		_rectTransform.from_json(j["rectTransform"]);
	}

private:
	RectTransform _rectTransform;
};
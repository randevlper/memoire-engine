#pragma once
#include "Engine/Nodes/Node.h"
#include "Engine/Data/RectTransform.h"

class NodeUI : public Node
{
public:
	NodeUI();
	virtual ~NodeUI();
	RectTransform rectTransform;

private:

};
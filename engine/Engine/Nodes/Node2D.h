#pragma once
#include "Node.h"
#include "Engine/Data/Transform.h"

class Node2D : public Node
{
public:
	Node2D();
	virtual ~Node2D();
	Transform transform;
private:

};
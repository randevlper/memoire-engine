#include "Node2D.h"

Node2D::Node2D()
{
	_type = "Node2D";
}

Node2D::~Node2D()
{

}

Transform Node2D::getTransform()
{
	return _transform;
}

void Node2D::setTransform(Transform transform)
{
	_transform = transform;
}

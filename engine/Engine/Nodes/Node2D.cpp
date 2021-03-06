#include "Node2D.h"

Node2D::Node2D()
{
	_type = "Node2D";
	_transform.setNode2D(this);
}

Node2D::~Node2D()
{

}

void Node2D::destroy()
{
	_transform.setParent(nullptr);
}

Transform Node2D::getTransform()
{
	return _transform;
}

void Node2D::setTransform(Transform transform)
{
	_transform = transform;
	_transform.setNode2D(this);
}

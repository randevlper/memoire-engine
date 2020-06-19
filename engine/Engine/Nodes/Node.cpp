#include "Node.h"

Node::Node()
{
	_name = "Node";
	_type = "Node";
}

Node::~Node()
{
}

void Node::render()
{
}

void Node::setName(std::string value) {
	_name = value;
}

std::string Node::getName() const {
	return _name;
}

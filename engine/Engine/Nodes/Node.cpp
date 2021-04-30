#include "Node.h"

Node::Node()
{
	_name = "Node";
	_type = "Node";
	_isEnabled = true;
	sort = 0;
}

Node::~Node()
{
}

void Node::render()
{
}

void Node::init()
{
}

void Node::tick()
{
}

void Node::destroy()
{
}

void Node::setName(std::string value) {
	_name = value;
}

std::string Node::getName() const {
	return _name;
}

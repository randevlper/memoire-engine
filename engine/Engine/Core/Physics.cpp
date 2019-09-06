#include "Engine/Core/Physics.h"
#include "glm/vec2.hpp"

Physics* Physics::_instance = nullptr;
glm::vec2 Physics::_gravity = { 0.0f, -9.81f };

void Physics::init()
{
	if (_instance == nullptr) {
		_instance = new Physics();
	}
}

Physics::Physics()
{

}

Physics::~Physics()
{

}

void Physics::quit()
{
	delete(_instance);
}

void Physics::tick()
{

}

void Physics::setGravity(glm::vec2& value)
{

}

glm::vec2 Physics::getGravity()
{
	return glm::vec2();
}

#include "Engine/Core/Physics.h"
#include "Engine/Nodes/Body.h"
#include "Engine/Utilities/Debug.h"
#include "glm/vec2.hpp"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


Physics* Physics::_instance = nullptr;
glm::vec2 Physics::_gravity = { 0.0f, -9.81f };

void Physics::init()
{
	if (_instance == nullptr) {
		_instance = DBG_NEW Physics();

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
	_gravity = value;
}

glm::vec2 Physics::getGravity()
{
	return _gravity;
}

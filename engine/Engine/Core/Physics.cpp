#include "Engine/Core/Physics.h"
#include "Engine/Nodes/Body.h"
#include "Engine/Utilities/Debug.h"
#include "glm/vec2.hpp"

#include "Engine/Utilities/DebugMemory.h"


Physics* Physics::_instance = nullptr;

void Physics::init(int argc, char** argv)
{
	if (_instance == nullptr) {
		_instance = DBG_NEW Physics();

		B2_NOT_USED(argc);
		B2_NOT_USED(argv);
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

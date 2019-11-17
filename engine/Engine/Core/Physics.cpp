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

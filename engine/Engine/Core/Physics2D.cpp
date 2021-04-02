#include "Engine/Core/Physics2D.h"
#include "Engine/Utilities/Debug.h"
#include "glm/vec2.hpp"

#include "Engine/Utilities/DebugMemory.h"


Physics2D* Physics2D::_instance = nullptr;

void Physics2D::init(int argc, char** argv)
{
	if (_instance == nullptr) {
		_instance = DBG_NEW Physics2D();

		B2_NOT_USED(argc);
		B2_NOT_USED(argv);
	}
}

Physics2D::Physics2D()
{

}

Physics2D::~Physics2D()
{

}

void Physics2D::quit()
{
	delete(_instance);
}

void Physics2D::tick()
{

}

#include "Engine/Core/Physics2D.h"

#include <string>
#include <glm/vec2.hpp>
#include <box2d/box2d.h>
#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

b2World* Physics2D::_world = nullptr;
glm::vec2 Physics2D::_gravity;
int32 Physics2D::_velocityIterations;
int32 Physics2D::_positionIterations;
float Physics2D::_timeStep;


void Physics2D::init(int argc, char** argv)
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	//Load Physics settings here?
	_gravity = { 0.0f, -10.0f };
	_timeStep = 1.0f / 60.0f;
	_velocityIterations = 6;
	_positionIterations = 2;

	_world = DBG_NEW b2World({ _gravity.x,_gravity.y });
}

void Physics2D::quit()
{
	delete(_world);
}

void Physics2D::tick()
{
	_world->Step(_timeStep, _velocityIterations, _positionIterations);
	
	b2Body* bodyList =_world->GetBodyList();

	while (bodyList != nullptr)
	{
		b2Vec2 pos = bodyList->GetPosition();
		 printf("%4.2f %4.2f\n", pos.x, pos.y);
		 bodyList = bodyList->GetNext();
	}
}

b2World* Physics2D::getWorld()
{
	return _world;
}

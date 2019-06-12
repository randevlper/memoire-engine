#include "GoldEngine/Core/Physics.h"
#include "glm/vec2.hpp"
#include "Box2D/Box2D.h"

Physics* Physics::_instance = nullptr;
b2World* Physics::_world = nullptr;
float Physics::_timeStep = 1.0f / 60.0f;
signed int Physics::_velocityIterations = 6;
signed int Physics::_positionIterations = 2;
glm::vec2 Physics::_gravity = { 0.0f, -9.81f };

void Physics::init()
{
	if (_instance == nullptr) {
		_instance = new Physics();
	}
}

Physics::Physics()
{
	_world = new b2World(b2Vec2(_gravity.x, _gravity.y));
}

Physics::~Physics()
{
	delete(_world);
}

void Physics::quit()
{
	delete(_instance);
}

b2Body* Physics::createBody(glm::vec2& pos, glm::vec2& size, int friction, int restitution, int density)
{
	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(pos.x, pos.y);
	b2PolygonShape polyShape;
	polyShape.SetAsBox(size.x, size.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polyShape;

	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	if (density > 0) {
		bodyDef.type = b2_dynamicBody;
	}

	b2Body* body = _world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	return body;
}

void Physics::tick()
{
	_world->Step(_timeStep, _velocityIterations, _positionIterations);
}

void Physics::setGravity(glm::vec2& value)
{
	_world->SetGravity(b2Vec2(value.x, value.y));
}

glm::vec2 Physics::getGravity()
{
	return glm::vec2(_world->GetGravity().x, _world->GetGravity().y);
}

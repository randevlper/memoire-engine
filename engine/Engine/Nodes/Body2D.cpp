#include "Body2D.h"

#include "Engine/Core/Physics2D.h"

#include <glm/vec2.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

Body2D::Body2D()
{
	_type = "Body2D";
	_body = nullptr;
}

Body2D::~Body2D()
{
	b2World* world = Physics2D::getWorld();
	world->DestroyBody(_body);
}

void Body2D::setupBox(float x, float y, float width, float height, Body2DType bodyType, bool isSensor)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(x, y);

	switch (bodyType)
	{
	case Body2DType::Static:
		bodyDef.type = b2BodyType::b2_staticBody;
		break;
	case Body2DType::Kinematic:
		bodyDef.type = b2BodyType::b2_kinematicBody;
		break;
	case Body2DType::Dynamic:
		bodyDef.type = b2BodyType::b2_dynamicBody;
		break;
	default:
		break;
	}

	//Create body here
	b2World* world = Physics2D::getWorld();
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(width, height);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.isSensor = isSensor;

	_body->CreateFixture(&fixtureDef);

	b2Vec2 position = _body->GetPosition();
	float angle = _body->GetAngle();
	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
}

void Body2D::setPosition(glm::vec2 pos)
{
	if (_body == nullptr) { return; }
	_body->SetTransform({ pos.x,pos.y }, _body->GetAngle());
}

glm::vec2 Body2D::getPosition()
{
	b2Vec2 p = _body->GetPosition();
	return {p.x, p.y};
}
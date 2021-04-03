#include "Body2D.h"

#include "Engine/Core/Physics2D.h"
#include "Engine/Utilities/Debug.h"

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
	if (_body == nullptr) { Debug::LogError("Why are you being destroyed when nullptr?"); return; }
	world->DestroyBody(_body);
}

void Body2D::setupBox(int x, int y, int width, int height, Body2DType bodyType, bool isSensor)
{
	float PPU = Physics2D::getPixelsPerUnit();
	b2BodyDef bodyDef;
	bodyDef.position.Set(x / PPU, y / PPU);

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
	//Should check here to make sure the Box created is not smaller then 0.1 Box2D units
	polygonShape.SetAsBox((width / 2) / PPU, (height/2) / PPU);
	
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
	float PPU = Physics2D::getPixelsPerUnit();
	_body->SetTransform({ pos.x /PPU,pos.y/PPU }, _body->GetAngle());
}

glm::vec2 Body2D::getPosition()
{
	b2Vec2 p = _body->GetPosition();
	return {p.x, p.y};
}
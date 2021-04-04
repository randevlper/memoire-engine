#include "Body2D.h"

#include "Engine/Core/Physics2D.h"
#include "Engine/Utilities/Debug.h"

#include <glm/vec2.hpp>

#include <box2d/b2_contact.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

Body2D::Body2D()
{
	_type = "Body2D";
	_body = nullptr;
	setupBox(0, 0, 10, 10, Body2DType::Static, 0x0001, 0x0001);
}

Body2D::~Body2D()
{
	b2World* world = Physics2D::getWorld();
	if (_body == nullptr) { Debug::LogError("Why are you being destroyed when nullptr?"); return; }
	world->DestroyBody(_body);
}

void Body2D::setupBox(int x, int y, int width, int height, Body2DType bodyType,
	uint16 category, uint16 mask, bool isSensor)
{
	//Create body here
	b2World* world = Physics2D::getWorld();
	
	if (_body != nullptr) { Debug::Log("Body has already been setup! - Rebuilding!");  world->DestroyBody(_body); }
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
	
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	//Should check here to make sure the Box created is not smaller then 0.1 Box2D units
	polygonShape.SetAsBox((width / 2) / PPU, (height/2) / PPU);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.isSensor = isSensor;
	fixtureDef.userData.pointer = (uintptr_t)this;

	fixtureDef.filter.categoryBits = category;
	fixtureDef.filter.maskBits = mask;
	

	_body->CreateFixture(&fixtureDef);

	b2Vec2 position = _body->GetPosition();
	float angle = _body->GetAngle();
}

void Body2D::setPosition(glm::vec2 pos)
{
	float PPU = Physics2D::getPixelsPerUnit();
	_body->SetTransform({ pos.x /PPU,pos.y/PPU }, _body->GetAngle());
}

glm::vec2 Body2D::getPosition()
{
	b2Vec2 p = _body->GetPosition();
	float PPU = Physics2D::getPixelsPerUnit();
	return {p.x * PPU, p.y * PPU};
}


void Body2D::setVelocity(glm::vec2 value)
{
	_body->SetLinearVelocity({ value.x, value.y });
}

void Body2D::setIsAwake(bool value)
{
	_body->SetAwake(value);
}

bool Body2D::isAwake()
{
	return _body->IsAwake();
}

void Body2D::setIsEnabled(bool value)
{
	_body->SetEnabled(value);
}

bool Body2D::isEnabled()
{
	return _body->IsEnabled();
}

Body2DType Body2D::getBodyType()
{
	switch (_body->GetType())
	{
	case b2BodyType::b2_staticBody:
		return Body2DType::Static;
	case b2BodyType::b2_kinematicBody:
		return Body2DType::Kinematic;
	case b2BodyType::b2_dynamicBody:
		return Body2DType::Dynamic;
	}
	return Body2DType::Static;
}

uint16 Body2D::getCatagory()
{
	return _body->GetFixtureList()->GetFilterData().categoryBits;
}

uint16 Body2D::getMask()
{
	return _body->GetFixtureList()->GetFilterData().maskBits;
}

bool Body2D::isSensor()
{
	return _body->GetFixtureList()->IsSensor();
}

void Body2D::OnContactStart(b2Contact* contact, Body2D* bodyA, Body2D* bodyB)
{

}

void Body2D::OnContactEnd(b2Contact* contact, Body2D* bodyA, Body2D* bodyB)
{

}

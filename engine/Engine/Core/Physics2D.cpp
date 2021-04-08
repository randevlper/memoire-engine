#include "Physics2D.h"

#include "Engine/Core/Renderer.h"

#include <string>
#include <glm/vec2.hpp>
#include <box2d/box2d.h>

#include "Engine/Nodes/Body2D.h"

#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

b2World* Physics2D::_world = nullptr;
glm::vec2 Physics2D::_gravity;
signed int  Physics2D::_velocityIterations;
signed int  Physics2D::_positionIterations;
float Physics2D::_timeStep;

signed int Physics2D::_pixelsPerUnit;

class b2ContactListenTest : public  b2ContactListener {
	void BeginContact(b2Contact* contact) override {
		Body2D* bodyA = (Body2D*)contact->GetFixtureA()->GetUserData().pointer;
		Body2D* bodyB = (Body2D*)contact->GetFixtureB()->GetUserData().pointer;
		bodyA->OnContactStart(Collision2D{ contact, bodyB });
		bodyB->OnContactStart(Collision2D{ contact, bodyA });
	}

	void EndContact(b2Contact* contact) override {
		Body2D* bodyA = (Body2D*)contact->GetFixtureA()->GetUserData().pointer;
		Body2D* bodyB = (Body2D*)contact->GetFixtureB()->GetUserData().pointer;
		bodyA->OnContactEnd(Collision2D{ contact, bodyB });
		bodyB->OnContactEnd(Collision2D{ contact, bodyA });
	}
};

static b2ContactListenTest contactListenTest;

void Physics2D::init(int argc, char** argv)
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	//Load Physics settings here?
	_gravity = { 0.0f, -10.0f };
	_timeStep = 1.0f / 60.0f;
	_velocityIterations = 6;
	_positionIterations = 2;

	_pixelsPerUnit = 100;

	_world = DBG_NEW b2World({ _gravity.x,_gravity.y });
	_world->SetContactListener(&contactListenTest);
}

void Physics2D::quit()
{
	delete(_world);
}

void Physics2D::tick()
{
	_world->Step(_timeStep, _velocityIterations, _positionIterations);
	
	b2Body* body =_world->GetBodyList();
	b2Vec2 pos;
	b2Vec2 vert;
	b2Fixture* fixtures;
	b2PolygonShape* polygonShape;
	Transform bodyTransform;

	while (body != nullptr)
	{
		Body2D* body2D = (Body2D*)body->GetFixtureList()->GetUserData().pointer;
		if (body2D != nullptr) {
			pos = body->GetPosition();
			bodyTransform = body2D->getTransform();
			bodyTransform.setLocalPosition({ pos.x * _pixelsPerUnit, pos.y * _pixelsPerUnit });
			body2D->setTransform(bodyTransform);
		}

		fixtures = body->GetFixtureList();
		if (fixtures->GetType() == b2Shape::Type::e_polygon) {
			polygonShape = (b2PolygonShape*)fixtures->GetShape();
			
			std::vector<glm::vec2> points;
			points.resize(polygonShape->m_count);
			for (size_t i = 0; i < polygonShape->m_count; i++)
			{
				 vert = body->GetWorldPoint(polygonShape->m_vertices[i]);
				 points[i] = { vert.x * _pixelsPerUnit, vert.y * _pixelsPerUnit };
			}

			Renderer::renderLines(points.data(), points.size(), glm::vec4(0, 255, 0, 255));
		}


		body = body->GetNext();
	}
}

b2World* Physics2D::getWorld()
{
	return _world;
}

signed int Physics2D::getPixelsPerUnit()
{
	return _pixelsPerUnit;
}

glm::vec2 Physics2D::getGravity()
{
	return { _world->GetGravity().x, _world->GetGravity().y };
}

void Physics2D::setGravity(glm::vec2 value)
{
	_world->SetGravity({ value.x, value.y });
}
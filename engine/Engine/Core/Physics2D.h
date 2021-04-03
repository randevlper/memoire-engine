#pragma once
#include <glm/fwd.hpp>
class b2World;

//TESTING -----------
#include "box2d/box2d.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Nodes/Body2D.h"

class b2ContactListenTest : public  b2ContactListener {
	void BeginContact(b2Contact* contact) override {
		Body2D* bodyA = (Body2D*)contact->GetFixtureA()->GetUserData().pointer;
		Body2D* bodyB = (Body2D*)contact->GetFixtureB()->GetUserData().pointer;
		bodyA->OnContactStart(contact, bodyA, bodyB);
		bodyB->OnContactStart(contact, bodyA, bodyB);
	}

	void EndContact(b2Contact* contact) override {
		Body2D* bodyA = (Body2D*)contact->GetFixtureA()->GetUserData().pointer;
		Body2D* bodyB = (Body2D*)contact->GetFixtureB()->GetUserData().pointer;
		bodyA->OnContactEnd(contact, bodyA, bodyB);
		bodyB->OnContactEnd(contact, bodyA, bodyB);
	}
};
//TESTING -----------

class Physics2D
{
public:
	static void init(int argc, char** argv);
	static void quit();
	static void tick();

	static b2World* getWorld();

	static signed int getPixelsPerUnit();

private:
	//Only need one world for now
	static b2World* _world;
	
	static signed int _pixelsPerUnit; 

	static glm::vec2 _gravity;
	static signed int _velocityIterations;
	static signed int _positionIterations;
	static float _timeStep;
	static b2ContactListenTest contactListenTest;
};
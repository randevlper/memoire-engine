#pragma once
#include <glm/fwd.hpp>
class b2World;

//TESTING -----------
#include "box2d/box2d.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Nodes/Body2D.h"

class b2ContactListenTest : public  b2ContactListener {
	void BeginContact(b2Contact* contact) override {
		Body2D* body = (Body2D*)contact->GetFixtureA()->GetUserData().pointer;
		Debug::Log(body->getType() + " Contact!");
	}

	void EndContact(b2Contact* contact) override {
		Debug::Log("EndContact!");
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
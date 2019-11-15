#pragma once
#include "glm/fwd.hpp"
#include <vector>
#include "Box2D/Box2D.h"

class Physics
{
public:
	static void init(int argc, char** argv);
	static void quit();
	static void tick();

	static void setGravity(glm::vec2& value);
	static glm::vec2 getGravity();

	static b2World* getWorld();

private:
	static Physics* _instance;
	static glm::vec2 _gravity;
	static b2World* _world;

	Physics();
	~Physics();
};
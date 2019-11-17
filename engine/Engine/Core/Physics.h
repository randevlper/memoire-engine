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

private:
	static Physics* _instance;

	Physics();
	~Physics();
};
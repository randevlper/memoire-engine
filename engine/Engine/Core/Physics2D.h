#pragma once
#include "glm/fwd.hpp"
#include <vector>
#include "Box2D/Box2D.h"

class Physics2D
{
public:
	static void init(int argc, char** argv);
	static void quit();
	static void tick();

private:
	static Physics2D* _instance;

	Physics2D();
	~Physics2D();
};
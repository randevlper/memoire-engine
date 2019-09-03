#pragma once
#include "glm/fwd.hpp"

class Physics
{
public:
	static void init();
	static void quit();
	static void tick();

	static void setGravity(glm::vec2& value);
	static glm::vec2 getGravity();

private:
	static Physics* _instance;
	static glm::vec2 _gravity;

	Physics();
	~Physics();
};
#pragma once
#include "glm/fwd.hpp"
class b2Body;
class b2World;

class Physics
{
public:
	static void init();
	static void quit();
	//Create Rectangle
	static b2Body* createBody(glm::vec2 &pos, glm::vec2 &size, int friction, int restitution, int density = 0);
	//Create Circle
	static b2Body* createBody(glm::vec2& pos, int radius, int friction, int restitution, int density = 0);
	static void tick();

	static void setGravity(glm::vec2& value);
	static glm::vec2 getGravity();

private:
	static Physics* _instance;
	static b2World* _world;
	static float _timeStep;
	static signed int _velocityIterations;
	static signed int _positionIterations;
	static glm::vec2 _gravity;

	Physics();
	~Physics();
};
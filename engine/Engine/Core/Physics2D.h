#pragma once
#include <glm/fwd.hpp>
class b2World;

class Physics2D
{
public:
	static void init(int argc, char** argv);
	static void quit();
	static void tick();

	static glm::vec2 getGravity();
	static void setGravity(glm::vec2 value);

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
};
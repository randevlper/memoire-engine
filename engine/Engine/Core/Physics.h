#pragma once
#include "glm/fwd.hpp"
#include <vector>

class Collider;

class Physics
{
public:
	static void init();
	static void quit();
	static void tick();

	static void setGravity(glm::vec2& value);
	static glm::vec2 getGravity();
	//Adds to physics sim
	static bool addCollider(Collider* col);
	//Removes from physics sim
	static bool removeCollider(Collider* col);

private:
	static Physics* _instance;
	static glm::vec2 _gravity;
	static std::vector<Collider*> _colliders;

	Physics();
	~Physics();
};
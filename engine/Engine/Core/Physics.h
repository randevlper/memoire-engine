#pragma once
#include "glm/fwd.hpp"
#include "glm/vec2.hpp"
#include "glm/mat3x3.hpp"
/*
DataTypes
	Polygon
	Collision
	AxialExtents

CheckCollisions
	Actor can have a
	Coliders
		Polygon

	Layers


*/

#define PHYSICS_POLYGON_MAX_POINTS 16 
#define PHYSICS_COLLIDERS_MAX 32

struct Polygon {
	//All local
	glm::vec2 points[PHYSICS_POLYGON_MAX_POINTS];
	glm::vec2 axes[PHYSICS_POLYGON_MAX_POINTS];
	size_t pointsNum;
};

struct AxialExtents {
	float min, max;
};

struct Collider {
	Polygon polygon;
	bool isStatic;
	//Parent
	//For now use pos
	glm::vec2 pos;

	void createAxes();
};

struct Collision {
	float penetration;
	glm::vec2 collisionNormal;
};


class Physics
{
public:
	static void init();
	static void quit();
	static void tick();

	

	static void setGravity(glm::vec2& value);
	static glm::vec2 getGravity();

	static Collider* colliderCreate(Collider& collider);
	static bool colliderDestroy(Collider* collider);

private:
	static Physics* _instance;
	static glm::vec2 _gravity;
	static Collider** _colliders;


	static Collision& doCollide(Collider* a, Collider* b);
	static void resolveCollision(Collider* a, Collider* b);
	static AxialExtents& evalAxialExtents(const glm::vec2& axis, const glm::vec2* points, size_t count);

	Physics();
	~Physics();
};
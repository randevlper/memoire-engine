#include "Engine/Core/Physics.h"
#include "glm/vec2.hpp"
#include "glm/gtx/normal.hpp"
#include "glm/gtx/perpendicular.hpp"

Physics* Physics::_instance = nullptr;
glm::vec2 Physics::_gravity = { 0.0f, -9.81f };
Collider** Physics::_colliders = new Collider * [PHYSICS_COLLIDERS_MAX];

void Physics::init()
{
	if (_instance == nullptr) {
		_instance = new Physics();
	}
}

Collision& Physics::doCollide(Collider* a, Collider* b)
{
	glm::vec2 axes[PHYSICS_POLYGON_MAX_POINTS * 2];

	int naxes = 0;
	for (int i = 0; i < a->polygon.pointsNum; ++i)
	{
		axes[naxes++] = a->polygon.axes[i];
	}
	for (int i = 0; i < b->polygon.pointsNum; ++i)
	{
		axes[naxes++] = b->polygon.axes[i];
	}

	float fPD = FLT_MAX;
	glm::vec2  fCN = {0,0};
	bool  res = true;

	for (int i = 0; i < naxes; ++i)
	{
		AxialExtents Aex = evalAxialExtents(axes[i], a->polygon.points, b->polygon.pointsNum);
		AxialExtents Bex = evalAxialExtents(axes[i], b->polygon.points, b->polygon.pointsNum);

		float lPD = Aex.max - Bex.min;
		float rPD = Bex.max - Aex.min;

		float PD = glm::min(lPD, rPD);
		float H = copysignf(1, lPD - rPD);
		glm::vec2 CN = axes[i] * H;

		res = res && PD >= 0;



		if ((res && PD < fPD) ||
			(!res && (PD < 0) && (PD > fPD || fPD >= 0)))
		{
			fPD = PD;
			fCN = CN;
		}

		if (!res)
		{
			return Collision{ fPD, fCN };
		}
	}

	return Collision{ fPD, fCN };
}

AxialExtents& Physics::evalAxialExtents(const glm::vec2& axis, const glm::vec2* points, size_t count)
{
	AxialExtents res = { INFINITY, -INFINITY };
	for (size_t i = 0; i < count; ++i) {
		float proj = glm::dot(axis, points[i]);
		res.min = glm::min(proj, res.min);
		res.max = glm::max(proj, res.max);
	}
	return res;
}

Physics::Physics()
{

}

Physics::~Physics()
{

}

void Physics::quit()
{
	operator delete[](_colliders);
	delete(_instance);
}

void Physics::tick()
{
	//Check if any collider collides
}

void Physics::setGravity(glm::vec2& value)
{

}

glm::vec2 Physics::getGravity()
{
	return glm::vec2();
}

void Collider::createAxes()
{
	for (int i = 0; i < polygon.pointsNum; ++i)
	{
		glm::vec2 ret = polygon.points[i] - polygon.points[(i + 1) % polygon.pointsNum];
		polygon.axes[i] = glm::normalize(glm::vec2(ret.y, -ret.x));
	}
}

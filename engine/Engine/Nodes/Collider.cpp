#include "Collider.h"
#include "Engine/Utilities/Debug.h"
#include <vector>

Collider::Collider() : isStatic(false), isDebug(false)
{
	geo.points.push_back({ 5, 5 });
	geo.points.push_back({ -5, 5 });
	geo.points.push_back({ -5, -5 });
	geo.points.push_back({ 5, -5 });
	Collider(geo.points);
}

Collider::Collider(std::vector<glm::vec2> &p) : isStatic(false), isDebug(false)
{
	geo.points = p;
	CreateAxes(geo);

}

Collider::~Collider()
{
}

Collision Collider::doesCollide(SATGeometry* A, SATGeometry* B)
{
	glm::vec2 axes[COLLIDER_MAX_POINTS * 2];

	int naxes = 0;
	for (int i = 0; i < A->points.size(); ++i)
	{
		axes[naxes++] = A->axes[i];
	}
	for (int i = 0; i < B->points.size(); ++i)
	{
		axes[naxes++] = B->axes[i];
	}

	float fPD = FLT_MAX;
	glm::vec2  fCN = glm::vec2();
	bool  res = true;

	for (int i = 0; i < naxes; ++i)
	{
		AxialExtents Aex = evalAxialExtents(axes[i], A->points);
		AxialExtents Bex = evalAxialExtents(axes[i], B->points);

		float lPD = Aex.max - Bex.min;
		float rPD = Bex.max - Aex.min;

		float PD = fmin(lPD, rPD);
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
			return Collision{ fPD, fCN, };
		}
	}

	return Collision{ fPD, fCN };
}

SATGeometry Collider::getWorldGeo()
{
	SATGeometry ret;
	glm::mat3x3 m = transform.getGlobalMatrix();
	for (size_t i = 0; i < geo.points.size(); i++)
	{
		ret.points.push_back(m * glm::vec3(geo.points[i], 1));
	}
	CreateAxes(ret);
	return ret;
}

Collision Collider::doesCollide(Collider* other)
{
	Collision retval = doesCollide(&getWorldGeo(), &other->getWorldGeo());
	retval.other = other;
	return retval;
}

void Collider::onEnter(const Collision& collision)
{
	if(isDebug){
		Debug::Log("Enter!");
	}
}

void Collider::onStay(const Collision& collision)
{
	if (isDebug) {
		Debug::Log("Stay!");
	}
	
}

void Collider::onExit(const Collision& collision)
{
	if (isDebug) {
		Debug::Log("Exit!");
	}
}

void Collider::addColliding(Collision other)
{
	_colliding.push_back(other);
}

void Collider::solveColliding()
{
	//TODO Clean this up

	//if new OnEnter

	//if already OnStay
	bool stay;
	for (size_t a = 0; a < _colliding.size(); a++)
	{
		stay = false;
		for (size_t b = 0; b < _collidingLastFrame.size(); b++)
		{
			if (_colliding[a].other == _collidingLastFrame[b].other) {
				//Stay
				onStay(_colliding[a]);
				stay = true;
			}
		}
		//onenter
		if (!stay) {
			onEnter(_colliding[a]);
		}
	}
	
	for (size_t a = 0; a < _collidingLastFrame.size(); a++)
	{
		stay = false;
		for (size_t b = 0; b < _colliding.size(); b++)
		{
			if (_collidingLastFrame[a].other == _colliding[b].other) {
				stay = true;
				break;
			}
		}
		if (!stay) {
			onExit(_collidingLastFrame[a]);
		}
	}
	
	//if gone OnExit
	_collidingLastFrame = _colliding;
	_colliding.clear();
}

void Collider::CreateAxes(SATGeometry &g)
{
	for (int i = 0; i < g.points.size(); ++i) {
		g.axes.push_back(glm::normalize(perp(g.points[i] - g.points[(i + 1) % g.points.size()])));
	}
}

//counterclockwise
glm::vec2 Collider::perp(glm::vec2& v)
{
	return glm::vec2(-v.y, v.x);
}

AxialExtents Collider::evalAxialExtents(glm::vec2& axis, std::vector<glm::vec2> &points)
{
	AxialExtents res = { INFINITY, -INFINITY };
	for (int i = 0; i < points.size(); ++i) {
		float proj = glm::dot(axis, points[i]);
		res.min = fmin(proj, res.min);
		res.max = fmax(proj, res.max);
	}
	return res;
}

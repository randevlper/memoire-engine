#include "Collider.h"
#include <vector>

Collider::Collider()
{
	points.push_back({ 5, 5 });
	points.push_back({ -5, 5 });
	points.push_back({ -5, -5 });
	points.push_back({ 5, -5 });
	CreateAxes();
}

Collider::Collider(std::vector<glm::vec2> &p)
{
	points = p;
	CreateAxes();
}

Collider::~Collider()
{
}

void Collider::CreateAxes()
{
	for (int i = 0; i < points.size(); ++i) {
		axes.push_back(glm::normalize(perp(points[i] - points[(i + 1) % points.size()])));
	}
}

//counterclockwise
glm::vec2 Collider::perp(glm::vec2& v)
{
	return glm::vec2(-v.y, v.x);
}

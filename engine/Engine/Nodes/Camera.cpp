#include "Camera.h"
#include "bgfx/bgfx.h"
#include "bx/bx.h"
#include "bx/math.h"
#include "glm/glm.hpp"
#include "Engine/Core/Context.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

float* Camera::getProjectionMatrix()
{
	float width = Context::getWindowWidth();
	float height = Context::getWindowHeight();

	float left = -(width) / 2;
	float right = (width) / 2;
	float bottom = -(height) / 2;
	float top = (height) / 2;
	bx::mtxOrtho(_proj, left, right, bottom, top, 0.1f, 100.0f, 0, bgfx::getCaps()->homogeneousDepth);
	return _proj;
}

float* Camera::getViewMatrix()
{
	glm::vec2 pos = transform.getPosition();
	bx::Vec3 at = { pos.x, pos.y,  0.0f };
	bx::Vec3 eye = { pos.x, pos.y, -10.0f };
	bx::mtxLookAt(_view, eye, at);
	return _view;
}

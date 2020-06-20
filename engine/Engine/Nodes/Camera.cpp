#include "Camera.h"
#include "bgfx/bgfx.h"
#include "bx/bx.h"
#include "bx/math.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Engine/Core/Context.h"

Camera::Camera()
{
	_type = "Camera";
}

Camera::~Camera()
{
}

glm::mat4* Camera::getProjectionMatrix()
{
	float width = Context::getWindowWidth();
	float height = Context::getWindowHeight();

	float proj[16];
	float left = -(width) / 2;
	float right = (width) / 2;
	float bottom = -(height) / 2;
	float top = (height) / 2;
	bx::mtxOrtho(proj, left, right, bottom, top, 0.1f, 100.0f, 0, bgfx::getCaps()->homogeneousDepth);
	memcpy(glm::value_ptr(_proj), proj, sizeof(proj));
	return &_proj;
}

glm::mat4* Camera::getViewMatrix()
{
	float view[16];
	glm::vec2 pos = transform.getPosition();
	bx::Vec3 at = { pos.x, pos.y,  0.0f };
	bx::Vec3 eye = { pos.x, pos.y, -10.0f };
	bx::mtxLookAt(view, eye, at);
	memcpy(glm::value_ptr(_view), view, sizeof(view));
	return &_view;
}

glm::vec2 Camera::screenToWorld(glm::vec2 pos)
{
	glm::mat4 proj = *getProjectionMatrix() * *getViewMatrix();

	float width = Context::getWindowWidth();
	float height = Context::getWindowHeight();

	glm::vec4 viewport = { 0, 0, width, height };

	float x = pos.x;
	float y = viewport[3] - pos.y;

	
	glm::vec3 worldCord = glm::unProject(glm::vec3(x, y, 0), glm::mat4(1.0f), proj, viewport);
	return { worldCord.x, worldCord.y};
}

nlohmann::json Camera::to_json()
{
	nlohmann::json retval = Node2D::to_json();
	retval["type"] = _type;
	return retval;
}

#pragma once
#include "Node2D.h"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"

class Camera : public Node2D
{
public:
	Camera();
	~Camera() override;

	glm::mat4* getProjectionMatrix();
	glm::mat4* getViewMatrix();
	glm::vec2 screenToWorld(glm::vec2 pos);

private:
	glm::mat4 _proj;
	glm::mat4 _view;
};
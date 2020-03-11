#pragma once
#include "Node.h"

class Camera : public Node
{
public:
	Camera();
	~Camera();

	float* getProjectionMatrix();
	float* getViewMatrix();

private:
	float _proj[16];
	float _view[16];
};
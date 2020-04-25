#pragma once
#include <glm/vec2.hpp>

#include "Transform.h"

class RectTransform
{
public:
	//Four corners
	RectTransform();
	~RectTransform();

	void setSize(glm::ivec2 value);
	void setPosition(glm::ivec2 value);

private:

	Transform _root;
	Transform _transforms[4];
};
#pragma once
#include <glm/vec2.hpp>

#include "Transform.h"
#define RECT_TRANSFORM_SIZE 4

class RectTransform
{
public:
	
	
	//Four corners
	RectTransform();
	~RectTransform();

	void setSize(glm::ivec2 value);
	void setPosition(glm::ivec2 value);
	void setRotation(float value);
	void setScale(glm::vec2 value);

	//Counter clockwise starting at bottom left
	glm::vec2* getScreenCorners();

private:

	Transform _root;
	Transform _transforms[4];

	glm::vec2 _corners[4];
};
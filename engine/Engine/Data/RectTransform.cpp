#include "RectTransform.h"

RectTransform::RectTransform()
{
	for (size_t i = 0; i < 4; i++)
	{
		_transforms[i].setParent(&_root);
	}
}

RectTransform::~RectTransform()
{
}

void RectTransform::setSize(glm::ivec2 value)
{
	_transforms[0].setLocalPosition({ 0, 0 });
	_transforms[1].setLocalPosition({ value.x, 0 });
	_transforms[2].setLocalPosition({ value.x, value.y });
	_transforms[3].setLocalPosition({ 0, value.y });
}

void RectTransform::setPosition(glm::ivec2 value)
{
	_root.setLocalPosition(value);
}

void RectTransform::setRotation(float value)
{
	_root.setLocalAngle(value);
}

void RectTransform::setScale(glm::vec2 value)
{
	_root.setLocalScale(value);
}

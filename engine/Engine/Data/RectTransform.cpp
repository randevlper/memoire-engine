#include "RectTransform.h"
#include "Engine/Utilities/TypeConversion.h"
#include "Engine/Utilities/glmJson.h"

#include "Engine/Core/Context.h"

RectTransform::RectTransform()
{
	for (size_t i = 0; i < RECT_TRANSFORM_SIZE; i++)
	{
		//_transforms[i].setParentTransform(&_root);
		_corners[i] = {0,0};
		_windowCorners[i] = { 0,0 };
	}
	_size = { 1,1 };
}

RectTransform::~RectTransform()
{
}

void RectTransform::setSize(glm::ivec2 value)
{
	_size = value;
	_transforms[0].setLocalPosition({ 0, 0 });
	_transforms[1].setLocalPosition({ value.x, 0 });
	_transforms[2].setLocalPosition({ value.x, value.y });
	_transforms[3].setLocalPosition({ 0, value.y });

	//TODO fix rect transform this is a bandaid
	for (unsigned int i = 0; i < RECT_TRANSFORM_SIZE; i++)
	{
		_transforms[i].setLocalPosition(_transforms[i].getLocalPosition() + _root.getLocalPosition());
	}
}

//Set in screen cords 0 - 1
void RectTransform::setPosition(glm::vec2 value)
{
	value.x /= ((float)Context::getWindowWidth()); //2 since openGL goes from -1 - 1
	value.y /= ((float)Context::getWindowHeight());
	_root.setLocalPosition(value);
}

glm::vec2 RectTransform::getPosition()
{
	glm::vec2 retval = _root.getLocalPosition();
	retval.x *= ((float)Context::getWindowWidth());
	retval.y *= ((float)Context::getWindowHeight());
	return retval;
}

void RectTransform::setRotation(float value)
{
	_root.setLocalAngle(value);
}

void RectTransform::setScale(glm::vec2 value)
{
	_root.setLocalScale(value);
}

glm::mat4x4 RectTransform::getGlobalMatrix()
{
	return _root.getGlobalMatrix();
}

//Returns corners in screen space OGL -1 to 1
glm::vec2* RectTransform::getScreenCorners()
{
	glm::vec2 pos = { 0,0 };
	for (size_t i = 0; i < RECT_TRANSFORM_SIZE; i++)
	{
		pos = me::util::convertPixelToScreen(_transforms[i].getPosition());
		_corners[i].x = pos.x;
		_corners[i].y = pos.y;
	}

	return _corners;
}

//Returns corners in window space
glm::vec2* RectTransform::getWindowCorners()
{
	glm::vec2 pos = { 0,0 };
	for (size_t i = 0; i < RECT_TRANSFORM_SIZE; i++)
	{
		_windowCorners[i] = _transforms[i].getPosition();
	}
	return _windowCorners;
}

nlohmann::json RectTransform::get_json()
{
	nlohmann::json j;
	j["size"] = _size;
	j["root"] = _root.get_json();
	return j;
}

void RectTransform::from_json(const nlohmann::json& j)
{
	_root.from_json(j["root"]);
	setSize(j.at("size"));
}

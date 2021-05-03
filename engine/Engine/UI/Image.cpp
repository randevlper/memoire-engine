#include "Image.h"

#include "Engine/Data/UniformTypes.h"
#include "Engine/Data/IndexTypes.h"

namespace me {
	namespace ui {
		Image::Image()
		{
			_type = "Image";
		}

		Image::~Image()
		{

		}


		void Image::render()
		{

		}

		glm::vec4 Image::getColor()
		{
			return _color;
		}
		void Image::setColor(glm::vec4 value)
		{
			_color = value;
		}
		void Image::setSprite(Sprite* sprite)
		{
			_sprite = sprite;
		}
		Sprite* Image::getSprite()
		{
			return _sprite;
		}
	}
}
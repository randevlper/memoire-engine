#include "Image.h"

#include "Engine/Data/VertexTypes.h"
#include "Engine/Data/UniformTypes.h"
#include "Engine/Data/IndexTypes.h"

#include "Engine/AssetManagement/Shader.h"
#include "Engine/AssetManagement/AssetManager.h"


namespace me {
	namespace ui {
		static Shader* shader;
		static bool isInit;
		Image::Image()
		{
			_type = "Image";
			if (!isInit) {
				me::data::PositionColorUVVertex::init();
				shader = AssetManager::get<Shader>("assets/shaders/vs_sprite.bin");
				isInit = true;
			}

			vbh = bgfx::createVertexBuffer(bgfx::makeRef(me::data::PositionColorUVVertex::verts, sizeof(me::data::PositionColorUVVertex::verts)), me::data::PositionColorUVVertex::layout);
			ibh = bgfx::createIndexBuffer(bgfx::makeRef(me::data::PositionColorUVVertex::indices, sizeof(me::data::PositionColorUVVertex::indices)));
			u_sprite = me::data::getSpriteUniform();
			u_color = me::data::getColorUniform();
			_sprite = nullptr;
			_color = { 1,1,1,1 };
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
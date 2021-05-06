#include "Image.h"

#include "Engine/Core/Renderer.h"
#include "Engine/Core/Context.h"

#include "Engine/Data/UniformTypes.h"
#include "Engine/Data/IndexTypes.h"

#include "Engine/AssetManagement/Shader.h"
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/AssetManagement/AssetManager.h"


namespace me {
	namespace ui {
		static Shader* shader;
		static bool isInit;
		Image::Image()
		{
			_type = "Image";
			if (!isInit) {
				me::data::PositionUVVertex::init();
				shader = AssetManager::get<Shader>("assets/shaders/vs_image.bin");
				isInit = true;
			}

			vbh = bgfx::createVertexBuffer(bgfx::makeRef(me::data::PositionUVVertex::verts, sizeof(me::data::PositionUVVertex::verts)), me::data::PositionUVVertex::layout);
			ibh = bgfx::createIndexBuffer(bgfx::makeRef(me::data::PositionUVVertex::indices, sizeof(me::data::PositionUVVertex::indices)));
			u_sprite = me::data::getSpriteUniform();
			u_color = me::data::getColorUniform();
			_sprite = nullptr;
			_color = { 1,1,1,1 };
		}

		Image::~Image()
		{
			bgfx::destroy(vbh);
			bgfx::destroy(ibh);
		}

		void Image::render()
		{
			if (_sprite == nullptr) { return; }
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_BLEND_ALPHA);
			//Transform t = _transform;
			//glm::mat4x4 m = t.getGlobalMatrix();
			//bgfx::setTransform(glm::value_ptr(m));
			bgfx::setVertexBuffer(0, vbh);
			bgfx::setIndexBuffer(ibh);
			bgfx::setUniform(u_color, &_color);

			if (bgfx::isValid(_sprite->handle)) {
				bgfx::setTexture(0, u_sprite, _sprite->handle);
			}

			bgfx::submit(UI_FRAME_BUFFER_INDEX, shader->getHandle(), sort);
		}

		glm::vec4 Image::getColor()
		{
			return _color;
		}
		void Image::setColor(glm::vec4 value)
		{
			_color = value;
		}
		nlohmann::json Image::to_json()
		{
			nlohmann::json j = NodeUI::to_json();
			if (_sprite != nullptr) {
				j["sprite"] = _sprite->path;
				j["parems"] = _sprite->parems;
			}
			else {
				j["sprite"] = "null";
			}

			j["color"] = _color;

			return j;
		}

		void Image::from_json(const nlohmann::json& j)
		{
			NodeUI::from_json(j);

			if (j["sprite"] != "null") {
				setSprite(AssetManager::getLoad<Sprite>(j["sprite"], j["parems"]));
			}
			_color = j["color"];
		}

		void Image::setSprite(Sprite* sprite)
		{
			_sprite = sprite;

			RectTransform t = getRectTransform();
			t.setSize({ sprite->width, sprite->height });
			setRectTransform(t);

			glm::vec2* corners = getRectTransform().getScreenCorners();

			

			memcpy(newVerts, me::data::PositionUVVertex::verts,
				sizeof(me::data::PositionUVVertex::verts));
			newVerts[0].xy({corners[0].x, corners[0].y});
			newVerts[1].xy({ corners[1].x, corners[1].y });
			newVerts[2].xy({ corners[2].x, corners[2].y });
			newVerts[3].xy({ corners[3].x, corners[3].y });

			vbh = bgfx::createVertexBuffer(bgfx::makeRef(newVerts, sizeof(newVerts)), me::data::PositionUVVertex::layout);
			//Screen space cords
		}
		Sprite* Image::getSprite()
		{
			return _sprite;
		}
	}
}
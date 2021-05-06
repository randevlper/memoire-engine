#pragma once
#include "NodeUI.h"

#include <bgfx/bgfx.h>
#include <glm/fwd.hpp>
#include "Engine/Data/VertexTypes.h"

class Sprite;
class Shader;

namespace me {
	namespace ui {
		class Image : public NodeUI
		{
		public:
			Image();
			~Image() override;

			void render() override;

			void setSprite(Sprite* sprite);
			Sprite* getSprite();

			glm::vec4 getColor();
			void setColor(glm::vec4 value);

			virtual nlohmann::json to_json() override;
			virtual void from_json(const nlohmann::json& j)  override;


		private:
			Sprite* _sprite;
			glm::vec4 _color;

			bgfx::VertexBufferHandle vbh;
			bgfx::IndexBufferHandle ibh;
			bgfx::UniformHandle u_sprite;
			bgfx::UniformHandle u_color;

			me::data::PositionUVVertex newVerts[4];
		};
	}
}


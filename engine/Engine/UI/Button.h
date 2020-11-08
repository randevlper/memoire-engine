#pragma once
#include "Engine/UI/NodeUI.h"

#include <functional>

#include <bgfx/bgfx.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Engine/Data/VertexTypes.h"
#include "Engine/Utilities/glmJson.h"

class Shader;
class Sprite;

namespace me {
	namespace ui {

		class Button : public NodeUI
		{
		public:
			Button();
			~Button() override;

			void sendMouseInfo(glm::vec2 mousePos, bool isClicking);
			void setSize(glm::vec2 size);
			
			void render() override;

			void setSprite(Sprite* value);

			//Normal Color
			glm::vec4 colorNormal;
			//Hover Color
			glm::vec4 colorHightlight;
			//Click Color
			glm::vec4 colorClicked;
			//Disabled Color
			glm::vec4 colorDisabled;

			std::function<void()> onClick;
			std::string luaOnClick;

			nlohmann::json to_json () override
			{
				nlohmann::json j = NodeUI::to_json();
				j["type"] = "Button";
				j["colorNormal"] = colorNormal;
				j["colorHightlight"] = colorHightlight;
				j["colorClicked"] = colorClicked;
				j["colorDisabled"] = colorDisabled;
				j["luaOnClick"] = luaOnClick;
				return j;
			}

			void from_json(const nlohmann::json& j) override
			{
				NodeUI::from_json(j);
				colorNormal = j.at("colorNormal");
				colorHightlight = j.at("colorHightlight");
				colorClicked = j.at("colorClicked");
				colorDisabled = j.at("colorDisabled");
				luaOnClick = j.at("luaOnClick");
				setSize(rectTransform.getSize());
			}
				
		private:

			static bool _isInit;
			static Shader* _shader;

			bool _lastIsMouseOver;
			bool _currentIsMouseOver;
			bool _lastMouseClicking;
			bool _currentMouseClicking;

			glm::vec2 _size;
			glm::vec4 _color;

			Sprite* _sprite;

			me::data::PositionUVVertex _verts[4];

			bgfx::UniformHandle _u_color;
			bgfx::UniformHandle _u_sprite;
			bgfx::VertexBufferHandle _vbh;
			bgfx::IndexBufferHandle _ibh;
		
			void setColor(glm::vec4 rgba);
		
		};
	}
}


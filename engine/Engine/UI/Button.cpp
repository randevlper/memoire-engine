#include "Button.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Shader.h"
#include "Engine/AssetManagement/Sprite.h"

#include "Engine/Core/LuaManager.h"

#include "Engine/Core/Context.h"
#include "Engine/Utilities/TypeConversion.h"

#include "Engine/Data/IndexTypes.h"
#include "Engine/Data/UniformTypes.h"

namespace me {
	namespace ui {
		//Button
		bool Button::_isInit = false;
		Shader* Button::_shader = nullptr;

		Button::Button()
		{
			_type = "Button";
			if (!_isInit) {
				me::data::PositionUVVertex::init();
				_shader = AssetManager::get<Shader>("assets/shaders/vs_ui.bin");
				_isInit = true;
			}

			_ibh = me::data::getPosUVVertIndexBufferHandle();
			_u_color = me::data::getColorUniform();
			_u_sprite = me::data::getSpriteUniform();

			_color = { 255,0,0,255 };

			_vbh.idx = bgfx::kInvalidHandle;
			
			_sprite = AssetManager::get<Sprite>("assets/ui/box.png");

			luaOnClick = "";

			setSize({ 10,10 });

			colorNormal = { 1,0,0, 1 };
			colorHightlight = { 0,1,0,1 };
			colorClicked = { 0,0,1,1 };
			colorDisabled = { 1,1,1,1};
		}

		Button::~Button()
		{
			bgfx::destroy(_vbh);
		}

		//Expects rawSDL window position
		//Should change this to have the UI manager/canvas to send the converted mouse pos to multiple buttons
		void Button::sendMouseInfo(glm::vec2 mousePos, bool isClicking)
		{
			_lastMouseClicking = _currentMouseClicking;
			_lastIsMouseOver = _currentIsMouseOver;
			_currentMouseClicking = isClicking;

			//Bounded box for now, no rotation
			glm::vec2* corners = rectTransform.getScreenCorners();
			mousePos.y = abs(mousePos.y - Context::getRenderHeight());
			glm::vec2 mouseScreen = me::util::convertPixelToScreen(mousePos);
			
			//Get Button state
			if (mouseScreen.x < corners[0].x || mouseScreen.x > corners[1].x) {
				_currentIsMouseOver = false;
			}
			else if (mouseScreen.y < corners[0].y || mouseScreen.y > corners[3].y) {
				_currentIsMouseOver = false;
			}
			else {
				_currentIsMouseOver = true;
			}
			
			//Button color
			if (_currentIsMouseOver && !_currentMouseClicking) {
				setColor(colorHightlight);
			}
			else if (_currentIsMouseOver && _currentMouseClicking) {
				setColor(colorClicked);
			}
			else {
				setColor(colorNormal);
			}

			//Call event
			if (_currentIsMouseOver && !_lastMouseClicking && _currentMouseClicking) {
				if (onClick) {
					onClick();
				}
				LuaManager::luaFunction(luaOnClick.c_str());
			}
		}

		//This should just be a plane that gets modifyed by shader

		//Takes size in screen pixels
		void Button::setSize(glm::vec2 size)
		{
			if (bgfx::isValid(_vbh)) {
				bgfx::destroy(_vbh);
			}

			_size = size;
			rectTransform.setSize(size);
			memcpy(_verts, me::data::PositionUVVertex::verts, sizeof(me::data::PositionUVVertex::verts));

			glm::vec2* corners = rectTransform.getScreenCorners();
			for (size_t i = 0; i < 4; i++)
			{
				_verts[i].xy(corners[i]);
				//Debug::Log("x: " + std::to_string(_verts[i].x) + " y: " + std::to_string(_verts[i].y));
			}

			_vbh = bgfx::createVertexBuffer(bgfx::makeRef(_verts, sizeof(_verts)), me::data::PositionUVVertex::layout);
		}

		//Expects value 0-1
		void Button::setColor(glm::vec4 rgba)
		{
			_color = rgba;
			//_color /= 255;
		}

		void Button::setSprite(Sprite* value) {
			_sprite = value;
		}


		void Button::render() {
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_BLEND_ALPHA, BGFX_STATE_BLEND_ADD);
			//bgfx::setTransform(glm::value_ptr(rectTransform.getGlobalMatrix()));
			if (_sprite != nullptr) {
				bgfx::setTexture(0, _u_sprite, _sprite->handle);
			}
			bgfx::setVertexBuffer(0, _vbh);
			bgfx::setIndexBuffer(_ibh);
			bgfx::setUniform(_u_color, glm::value_ptr(_color));
			bgfx::submit(0, _shader->getHandle());
		}
	}
}
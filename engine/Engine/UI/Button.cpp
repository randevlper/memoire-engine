#include "Button.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Shader.h"

#include "Engine/Core/Context.h"
#include "Engine/Utilities/TypeConversion.h"

namespace me {
	namespace ui {
		//Button
		bool Button::_isInit = false;
		Shader* Button::_shader = nullptr;

		Button::Button()
		{
			if (!_isInit) {
				me::data::PositionUVVertex::init();
				_shader = AssetManager::get<Shader>("assets/shaders/vs_ui.bin");
				_isInit = true;
			}

			_ibh = bgfx::createIndexBuffer(bgfx::makeRef(me::data::PositionUVVertex::planeTriList, sizeof(me::data::PositionUVVertex::planeVerts)));
			_u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);
			_color = { 255,0,0,255 };

			_vbh.idx = bgfx::kInvalidHandle;
			
			setSize({ 10,10 });

			colorNormal = { 255,0,0, 255 };
			colorHightlight = { 0,255,0,255 };
			colorClicked = { 0,0,255,255 };
			colorDisabled = { 100,100,100,255 };
		}

		Button::~Button()
		{
			bgfx::destroy(_u_color);
			bgfx::destroy(_vbh);
			bgfx::destroy(_ibh);
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
			mousePos.y = abs(mousePos.y - Context::getWindowHeight());
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
				onClick();
			}
		}

		//UI should not be changing size often
		//This will need to be changed for UI animation

		//Takes size in screen pixels
		void Button::setSize(glm::vec2 size)
		{
			if (bgfx::isValid(_vbh)) {
				bgfx::destroy(_vbh);
			}

			_size = size;
			rectTransform.setSize(size);
			memcpy(_verts, me::data::PositionUVVertex::planeVerts, sizeof(me::data::PositionUVVertex::planeVerts));

			glm::vec2* corners = rectTransform.getScreenCorners();
			for (size_t i = 0; i < 4; i++)
			{
				_verts[i].xy(corners[i]);
				Debug::Log("x: " + std::to_string(_verts[i].x) + " y: " + std::to_string(_verts[i].y));
			}

			_vbh = bgfx::createVertexBuffer(bgfx::makeRef(_verts, sizeof(_verts)), me::data::PositionUVVertex::layout);
		}

		//Expects value 0-255
		void Button::setColor(glm::vec4 rgba)
		{
			_color = rgba;
			_color /= 255;
		}

		void Button::render() {
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_BLEND_ALPHA, BGFX_STATE_BLEND_ADD);
			//bgfx::setTransform(glm::value_ptr(rectTransform.getGlobalMatrix()));
			bgfx::setVertexBuffer(0, _vbh);
			bgfx::setIndexBuffer(_ibh);
			bgfx::setUniform(_u_color, glm::value_ptr(_color));
			bgfx::submit(0, _shader->getHandle());
		}
	}
}
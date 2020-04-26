#include "Button.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Shader.h"

#include "Engine/Core/Context.h"
#include "Engine/Utilities/TypeConversion.h"

namespace me {
	namespace ui {
		//ButtonVertex
		bgfx::VertexLayout ButtonVertex::pcvLayout;
		ButtonVertex ButtonVertex::planeVerts[] = {
			{0.0f, 0.0f, 0.0f, 0, 0x7fff},
			{1.0f, 0.0f, 0.0f, 0x7fff, 0x7fff},
			{1.0f, 1.0f, 0.0f, 0x7fff, 0},
			{0.0f, 1.0f, 0.0f, 0, 0}
		};
		const uint16_t ButtonVertex::planeTriList[] = {
			0,1,2,
			0,2,3
		};

		void ButtonVertex::init() {
			pcvLayout.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
				.end();
		}
		
		//Button
		bool Button::_isInit = false;
		Shader* Button::_shader = nullptr;

		Button::Button()
		{
			if (!_isInit) {
				ButtonVertex::init();
				_shader = AssetManager::get<Shader>("assets/shaders/vs_ui.bin");
				_isInit = true;
			}

			_ibh = bgfx::createIndexBuffer(bgfx::makeRef(ButtonVertex::planeTriList, sizeof(ButtonVertex::planeTriList)));
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
			memcpy(_verts, ButtonVertex::planeVerts, sizeof(ButtonVertex::planeVerts));

			glm::vec2* corners = rectTransform.getScreenCorners();
			for (size_t i = 0; i < 4; i++)
			{
				_verts[i].xy(corners[i]);
				Debug::Log("x: " + std::to_string(_verts[i].x) + " y: " + std::to_string(_verts[i].y));
			}

			_vbh = bgfx::createVertexBuffer(bgfx::makeRef(_verts, sizeof(_verts)), ButtonVertex::pcvLayout);
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
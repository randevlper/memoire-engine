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
		}

		Button::~Button()
		{
			bgfx::destroy(_u_color);
			bgfx::destroy(_vbh);
			bgfx::destroy(_ibh);
		}

		bool Button::isMouseOver(glm::vec2 mousePos)
		{
			return false;
		}

		//UI should not be changing size often
		//This will need to be changed for UI animation

		//Takes size in screen pixels
		void Button::setSize(glm::vec2 size)
		{
			if (bgfx::isValid(_vbh)) {
				bgfx::destroy(_vbh);
			}

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

		void Button::destroy()
		{
		}
	}
}
#include "Text.h"

#include <algorithm>

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Font.h"
#include "Engine/AssetManagement/Shader.h"

#include "Engine/Data/VertexTypes.h"
#include "glm/gtc/type_ptr.hpp"

namespace me {
	namespace ui {
		
		Shader* Text::_shader = nullptr;
		bool Text::_isInit = false;
		
		Text::Text()
		{
			if (!_isInit) {
				_shader = AssetManager::get<Shader>("assets/shaders/vs_sprite.bin");
				_isInit = true;
			}

			_ibh = bgfx::createIndexBuffer(
				bgfx::makeRef(me::data::PositionColorUVVertex::indices, 
					sizeof(me::data::PositionColorUVVertex::indices)));
			_u_sprite = bgfx::createUniform("s_sprite", bgfx::UniformType::Sampler);
			_u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);
			_font = nullptr;
			_text = "";

			_color = { 255,255,255,255 };
			_percentRender = 1.0f;
		}

		Text::~Text()
		{
			clearVertexBuffers();
			bgfx::destroy(_ibh);
			bgfx::destroy(_u_sprite);
			bgfx::destroy(_u_color);
		}

		void Text::setColor(glm::vec4 value)
		{
			_color = (value / 255.0f);
		}

		void Text::setPercentRender(float value)
		{
			_percentRender = std::clamp(value, 0.0f, 1.0f);
		}

		void Text::render()
		{
			for (size_t i = 0; i < _vbs.size() * _percentRender; i++)
			{
				if (!bgfx::isValid(_vbs[i])) { continue; }
				bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_BLEND_ALPHA, BGFX_STATE_BLEND_ADD);
				//bgfx::setTransform(glm::value_ptr(transform.getGlobalMatrix()));
				bgfx::setVertexBuffer(0, _vbs[i]);
				bgfx::setIndexBuffer(_ibh);
				bgfx::setTexture(0, _u_sprite, _font->getCharacter(_text[i]).Handle);
				//bgfx::setUniform(_u_color, glm::value_ptr(_color));
				bgfx::submit(0, _shader->getHandle());
			}
		}

		void Text::setFont(Font* font)
		{
			_font = font;
			clearVertexBuffers();
			buildVertexBuffers();
		}

		void Text::setText(std::string value)
		{
			_text = value;
			clearVertexBuffers();
			buildVertexBuffers();
		}

		void Text::buildVertexBuffers()
		{
			if (_font == nullptr) { return; }
			if (_text == "") { return; }


		}

		void Text::clearVertexBuffers()
		{
			for (size_t i = 0; i < _vbs.size(); i++)
			{
				if (bgfx::isValid(_vbs[i])) {
					bgfx::destroy(_vbs[i]);
				}
			}
			_vbs.clear();
		}
	}
}
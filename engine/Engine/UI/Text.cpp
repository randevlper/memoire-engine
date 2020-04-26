#include "Text.h"

#include <algorithm>

#include <glm/gtc/type_ptr.hpp>

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Font.h"
#include "Engine/AssetManagement/Shader.h"

#include "Engine/Core/Context.h"

#include "Engine/Data/VertexTypes.h"
#include "Engine/Utilities/TypeConversion.h"

namespace me {
	namespace ui {
		
		Shader* Text::_shader = nullptr;
		bool Text::_isInit = false;
		
		Text::Text()
		{
			if (!_isInit) {
				_shader = AssetManager::get<Shader>("assets/shaders/vs_uisprite.bin");
				_isInit = true;
			}

			_ibh = bgfx::createIndexBuffer(
				bgfx::makeRef(me::data::PositionColorUVVertex::indices, 
					sizeof(me::data::PositionColorUVVertex::indices)));
			_u_sprite = bgfx::createUniform("u_sprite", bgfx::UniformType::Sampler);
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
			buildVertexBuffers();
		}

		void Text::setText(std::string value)
		{
			_text = value;
			buildVertexBuffers();
		}

		void Text::buildVertexBuffers()
		{
			if (_font == nullptr) { return; }
			if (_text == "") { return; }

			clearVertexBuffers();

			glm::vec2* corners = rectTransform.getWindowCorners();

			float x = corners[3].x;
			float y = corners[3].y;

			for (size_t i = 0; i < _text.size(); i++)
			{
				if (_text[i] == '\n') {
					bgfx::VertexBufferHandle invVbh;
					invVbh.idx = BGFX_INVALID_HANDLE;
					_vbs.push_back(invVbh);

					//https://stackoverflow.com/questions/28009564/new-line-pixel-distance-in-freetype
					//Take a look at this to fix spacing

					Character ch = _font->getCharacter('T');
					x = 0;
					y -= (ch.size.y + 10);
				}
				else {
					Character ch = _font->getCharacter(_text[i]);

					float xpos = x + ch.bearing.x;
					float ypos = y - (ch.size.y - ch.bearing.y);

					float w = ch.size.x;
					float h = ch.size.y;

					me::data::PositionColorUVVertex lineData[4];
					memcpy(lineData, me::data::PositionColorUVVertex::verts, sizeof(me::data::PositionColorUVVertex::verts));
					
					lineData[0].xy(me::util::convertPixelToScreen({ xpos, ypos }));
					lineData[1].xy(me::util::convertPixelToScreen({ xpos + w, ypos }));
					lineData[2].xy(me::util::convertPixelToScreen({ xpos + w, ypos + h }));
					lineData[3].xy(me::util::convertPixelToScreen({ xpos, ypos + h }));

					bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::copy(lineData, sizeof(lineData)), me::data::PositionColorUVVertex::layout);

					_vbs.push_back(vbh);
					x += (ch.advance >> 6);
				}
			}
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
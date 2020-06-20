#include "UniformTypes.h"

namespace me {
	namespace data {
		static bgfx::UniformHandle u_sprite;
		static bgfx::UniformHandle u_color;

		static bool spriteInit = false;
		static bool colorInit = false;

		bgfx::UniformHandle getSpriteUniform()
		{
			if (!spriteInit) {
				u_sprite = bgfx::createUniform("u_sprite", bgfx::UniformType::Sampler);
				spriteInit = true;
			}
			return u_sprite;
		}
		bgfx::UniformHandle getColorUniform()
		{
			if (!colorInit) {
				u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);
				colorInit = true;
			}
			return u_color;
		}
	}
}
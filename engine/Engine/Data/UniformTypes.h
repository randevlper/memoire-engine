#pragma once
#include <bgfx/bgfx.h>

namespace me {
	namespace data {
		//u_sprite Sampler
		bgfx::UniformHandle getSpriteUniform();
		//u_color Vec4
		bgfx::UniformHandle getColorUniform();
	}
}
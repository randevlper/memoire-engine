#include "Shader.h"

#include <bgfx/bgfx.h>

Shader::Shader(bgfx::ProgramHandle& handle)
{
	_handle = handle;
}

Shader::~Shader()
{
	bgfx::destroy(_handle);
}
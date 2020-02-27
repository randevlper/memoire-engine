#pragma once
#include "Asset.h"

#include <bgfx/bgfx.h>

class Shader : public Asset
{
public:
	Shader(bgfx::ProgramHandle& handle);
	~Shader() override;

	bgfx::ProgramHandle getHandle() {
		return _handle;
	}

private:
	bgfx::ProgramHandle _handle;
};
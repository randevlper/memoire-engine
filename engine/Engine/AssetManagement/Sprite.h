#pragma once
#include "Asset.h"

#include <bgfx/bgfx.h>
#include <glm/vec4.hpp>

class Sprite : public Asset
{
public:
	Sprite();
	Sprite(bgfx::TextureHandle handle, uint16_t width, uint16_t height, bool hasMips, 
		uint16_t numLayers, bgfx::TextureFormat::Enum format, 
		uint16_t flags = 0Ui64, const bgfx::Memory * mem = (const bgfx::Memory*)0);
	~Sprite() override;
	//~Asset() override;
	/*
	Texture
	*/
	void setPixel(unsigned int index, char r, char g, char b, char a);

	//Change to getHandle
	bgfx::TextureHandle handle;
	int width, height;

private:
	const bgfx::Memory* _memory;
	const bgfx::Memory* _memoryTemp;
	bool _hasMips;
	uint16_t _numLayers, _flags;
	bgfx::TextureFormat::Enum _format;
};

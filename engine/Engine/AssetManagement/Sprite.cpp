#include "Sprite.h"
#include <chrono>
#include "Engine/Utilities/Debug.h"

Sprite::Sprite(bgfx::TextureHandle handle, uint16_t width, uint16_t height, bool hasMips, uint16_t numLayers, bgfx::TextureFormat::Enum format, uint16_t flags, const bgfx::Memory* mem)
{
	this->handle = handle;
	this->width = width;
	this->height = height;
	this->_memory = bgfx::copy(mem->data, mem->size);
	_memoryTemp = nullptr;
	_hasMips = hasMips;
	_numLayers = numLayers;
	_flags = flags;
	_format = format;
}

Sprite::~Sprite()
{
	bgfx::destroy(handle);
	delete(_memory);
}

void Sprite::setPixel(unsigned int index, char r, char g, char b, char a)
{
	//std::chrono::time_point<std::chrono::steady_clock> start;
	//std::chrono::time_point<std::chrono::steady_clock> end;
	//start = std::chrono::steady_clock::now();


	//Current CPU performace is 0.0274~ms for a 32x32 texture

	//Only using PNGs at the moment RGBA
	unsigned int pos = (index * 4);
	//Could copy the data from the rbga value directly but this is fine
	_memory->data[pos] = r;
	_memory->data[pos + 1] = g;
	_memory->data[pos + 2] = b;
	_memory->data[pos + 3] = a;

	//Should queue this calls so multiple can be done in one frame
	//This is really expensive? should be able to modify data directly on the GPU but dont
	//know how with BGFX right now

	//BGFX gets rid of the memory sent to the GPU
	_memoryTemp = bgfx::copy(_memory->data, _memory->size);
	
	//Get rid of the old texture
	bgfx::destroy(handle);
	
	handle = bgfx::createTexture2D(
		width,
		height,
		_hasMips,
		_numLayers,
		_format,
		_flags,
		_memoryTemp
	);

	//end = std::chrono::steady_clock::now();
	//auto val = std::chrono::duration_cast<std::chrono::nanoseconds>(end.time_since_epoch()) - std::chrono::duration_cast<std::chrono::nanoseconds>(start.time_since_epoch());
	//Debug::Log(std::to_string(val.count()));
}

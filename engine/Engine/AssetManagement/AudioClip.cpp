#include "AudioClip.h"

#include <bgfx/bgfx.h>

#include "Engine/Data/Memory.h"

AudioClip::AudioClip(me::Memory* data)
{
	_memory = data;
}

AudioClip::~AudioClip() {
	me::destroy(_memory);
}

me::Memory* AudioClip::getData()
{
	return _memory;
}

#pragma once
#include "Asset.h"

namespace me {
	struct Memory;
}

class AudioClip : public Asset
{
public:
	AudioClip(me::Memory* data);
	~AudioClip() override;

	me::Memory* getData();

private:
	me::Memory* _memory;
};
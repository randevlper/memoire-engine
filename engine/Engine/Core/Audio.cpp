#include "Audio.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

/*
Refactor thoughts

Asset : AudioClip
One copy of the data Initial decoder for getting file formats

Node : AudioSource
Multiple Devices and Decoders
*/

int Audio::init()
{
	return 0;
}

void Audio::destroy()
{
}

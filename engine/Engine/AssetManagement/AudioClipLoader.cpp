#include "AudioClipLoader.h"

#define DR_MP3_IMPLEMENTATION
#include <extras/dr_mp3.h>   /* Enables MP3 decoding. */
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#include "Engine/Data/Memory.h"

#include "Engine/AssetManagement/AudioClip.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

AudioClipLoader::AudioClipLoader() {

}

AudioClipLoader::~AudioClipLoader() {

}

void AudioClipLoader::init()
{
	//Debug::Log("Unimplemented Loader Init");
}

void AudioClipLoader::destroy()
{
	//Debug::Log("Unimplemented Loader Destroy");
}

Asset* AudioClipLoader::load(std::string path, std::string vars)
{
	//Debug::Log("AudioClip Loader Load");
	return DBG_NEW AudioClip(me::readBinaryFile(path.c_str()));
}

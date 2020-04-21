#include "AudioClipLoader.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/AssetManagement/AudioClip.h"

AudioClipLoader::AudioClipLoader() {

}

AudioClipLoader::~AudioClipLoader() {

}

void AudioClipLoader::init()
{
	Debug::Log("Unimplemented Loader Init");
}

void AudioClipLoader::destroy()
{
	Debug::Log("Unimplemented Loader Destroy");
}

Asset* AudioClipLoader::load(std::string path, std::string vars)
{
	Debug::Log("Unimplemented Loader Load");
	return nullptr;
}

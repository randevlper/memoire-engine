#include "Audio.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

#include "Engine/Core/World.h"


/*
//Initial Implementation
TODO An Audio source for two audio tracks to be able to smooth between them? [Polish]
TODO Expandable number of individual sounds? [Polish]

Audio hosts its own World to store the audio nodes for now
No 3D audio in a VN so its not an issue
*/

#define SOUNDS_GROUP_SIZE 5

World* Audio::_audioWorld = nullptr;
AudioSource* Audio::_bgm = nullptr;
bool Audio::_bgmMuted = false;
std::vector<AudioSource*> Audio::_sounds = std::vector<AudioSource*>();


int Audio::init()
{
	_audioWorld = new World();
	_bgm = _audioWorld->create<AudioSource>();
	for (size_t i = 0; i < SOUNDS_GROUP_SIZE; i++)
	{
		_sounds.push_back(_audioWorld->create<AudioSource>());
	}

	return 0;
}

void Audio::destroy()
{
	delete(_audioWorld);
}

void Audio::playBGM(AudioClip* clip)
{
	_bgm->stop();
	//need to be able to stop the bgm first
	_bgm->setAudioClip(clip);
	_bgm->play();
	_bgm->setVolume(_bgmMuted ? 0.0f : 1.0f);

}

void Audio::muteBGM(bool value)
{
	_bgmMuted = value;
	_bgm->setVolume(_bgmMuted ? 0.0f : 1.0f);
}

void Audio::playSound(AudioClip* sound)
{
	for (size_t i = 0; i < _sounds.size(); i++)
	{
		if (!_sounds[i]->isPlaying()) {
			_sounds[i]->setAudioClip(sound);
			_sounds[i]->play();
			break;
		}
	}
}

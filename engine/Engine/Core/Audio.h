#pragma once
#include <vector>
#include "Engine/Nodes/AudioSource.h"

class World;
class AudioClip;

class Audio
{
public:
	static int init();
	static void destroy();

	static void playBGM(AudioClip* clip);
	static void muteBGM(bool value);
	static bool getIsBGMMuted() {
		return _bgmMuted;
	}

	static void playSound(AudioClip* sound);

private:
	static World* _audioWorld;
	
	static AudioSource* _bgm;
	static bool _bgmMuted;

	static std::vector<AudioSource*> _sounds;
};
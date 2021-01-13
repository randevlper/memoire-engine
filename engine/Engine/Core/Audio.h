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
	static void playSound(AudioClip* sound);

private:
	static World* _audioWorld;
	
	static AudioSource* _bgm;
	static std::vector<AudioSource*> _sounds;
};
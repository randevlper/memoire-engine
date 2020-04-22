#pragma once
#include "Engine/Nodes/Node.h"
class AudioClip;
struct ma_device;
struct ma_decoder;

class AudioSource : public Node
{
public:
	AudioSource();
	~AudioSource() override;

	bool setAudioClip(AudioClip* clip);
	void play();
	void stop();

private:
	unsigned int _frame;
	ma_device* _device;
	ma_decoder* _decoder;
	AudioClip* _clip;
};
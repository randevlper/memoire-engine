#pragma once
#include "Engine/Nodes/Node2D.h"
class AudioClip;
struct ma_device;
struct ma_decoder;

class AudioSource : public Node2D
{
public:
	AudioSource();
	~AudioSource() override;

	bool setAudioClip(AudioClip* clip);
	void play();
	void stop();

	bool isPlaying();

	nlohmann::json to_json() override {
		nlohmann::json j = Node2D::to_json();
		j["type"] = "AudioSource";
		return j;
	}

	void from_json(const nlohmann::json& j) override {

	}

	struct UserData
	{
		ma_decoder* decoder;
		bool* isPlaying;
		unsigned int frame;
	};

private:

	//Used to hold onto the pointer for cleanup
	//THIS DATA IS BEING MODIFIED BY ANOTHER THREAD - POssibly add some kind of safety to it
	UserData* _userData;

	//ONLY THE AUDIO THREAD SHOULD MODIFY THIS
	bool* _isPlaying;
	
	ma_device* _device;
	ma_decoder* _decoder;
	AudioClip* _clip;
};
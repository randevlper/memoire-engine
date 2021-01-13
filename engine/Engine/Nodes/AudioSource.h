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

	nlohmann::json to_json() override {
		nlohmann::json j = Node2D::to_json();
		j["type"] = "AudioSource";
		return j;
	}

	void from_json(const nlohmann::json& j) override {

	}

private:
	unsigned int _frame;
	ma_device* _device;
	ma_decoder* _decoder;
	AudioClip* _clip;
};
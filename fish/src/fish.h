#pragma once
#include "Engine/Physics2D/Body2D.h"
#include "fishData.h"

class SpriteRenderer;
class Hook;

class Fish : public Body2D
{
public:
	Fish();

	void init() override;
	void destroy() override;

	void attach(Hook* hook);
	void disconnect();

	void from_json(const nlohmann::json& j) override;
	nlohmann::json to_json() override;

	int getScore() {
		return _score;
	}
	void setScore(int value) {
		_score = value;
	}

	float getSpeed() {
		return _speed;
	}
	void setSpeed(float value) {
		_speed = value;
	}

	void setFishData(FishData value);
	FishData getFishData();

	SpriteRenderer* getSpriteRenderer();
private:
	int _score;
	float _speed;
	SpriteRenderer* _spriteRenderer;
	FishData _fishData;
};

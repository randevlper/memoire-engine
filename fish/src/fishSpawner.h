#pragma once
#include "Engine/Nodes/Node2D.h"
class World;

class FishSpawner : public Node2D
{
public:
	FishSpawner();

	void init() override;
	void tick() override;

	nlohmann::json to_json() override;
	void from_json(const nlohmann::json& j) override;

	int getSpawnDir() {
		return _spawnDir;
	}
	void setSpawnDir(int value) {
		_spawnDir = value;
	}

	float getSpeed() {
		return _speed;
	}
	void setSpeed(float value) {
		_speed = value;
	}

	float getTime() {
		return _time;
	}
	void setTime(float value) {
		_time = value;
	}

private:

	World* _world;

	int _spawnDir;
	float _speed;
	float _time;

	float _timer;
	
};
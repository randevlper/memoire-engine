#pragma once
#include "Engine/Nodes/Node2D.h"
class World;
class Fish;

class FishSpawner : public Node2D
{
public:
	FishSpawner();

	void spawn(Fish* fish);

	nlohmann::json to_json() override;
	void from_json(const nlohmann::json& j) override;

	int getSpawnDir() {
		return _spawnDir;
	}
	void setSpawnDir(int value) {
		_spawnDir = value;
	}

private:
	int _spawnDir;
	
};
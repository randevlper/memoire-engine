#pragma once
#include "Engine/Nodes/Node.h"

#include <random>
#include <vector>

#include "fish.h"

class FishSpawner;

class FishSpawnerManager : public Node
{
public:
	FishSpawnerManager();

	void init() override;
	void tick() override;

	void from_json(const nlohmann::json& j) override;
	nlohmann::json to_json() override;

	void setFishData(std::vector<FishData> fishData);

private:
	std::vector<FishData> _fishData;
	std::vector<FishSpawner*> _fishSpawners;
	float _time;
	float _timer;

	std::random_device _rand;
	std::mt19937 _gen;
	std::uniform_int_distribution<> _distribution;
	std::uniform_int_distribution<> _fishDist;
};
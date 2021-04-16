#pragma once
#include "Engine/Nodes/Node.h"

#include <random>
#include <vector>

class FishSpawner;

class FishSpawnerManager : public Node
{
public:
	FishSpawnerManager();

	void init() override;
	void tick() override;

	void from_json(const nlohmann::json& j) override;
	nlohmann::json to_json() override;

private:
	std::vector<FishSpawner*> _fishSpawners;
	float _time;
	float _timer;

	std::random_device _rand;
	std::mt19937 _gen;
	std::uniform_int_distribution<> _distribution;


};
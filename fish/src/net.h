#pragma once
#include "Engine/Physics2D/Body2D.h"

#include <vector>
#include <functional>

class Fish;
//attached to the boat, hook automatically moves up to this
//Handles the catching of fish
//Player controller talks to this to get 

class Net : public Body2D
{
public:
	Net();

	void init() override;

	std::function<void(std::vector<Fish*>)> CaughtFish;
	void OnContactStart(Collision2D collision) override;
private:

};
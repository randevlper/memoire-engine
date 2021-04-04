#pragma once
#include "Engine/Nodes/Body2D.h"

class FishKiller : public Body2D
{
public:
	FishKiller();

	void OnContactStart(b2Contact* contact, Body2D* bodyA, Body2D* bodyB) override;

private:

};
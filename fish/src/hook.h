#pragma once
#include "Engine/Nodes/Body2D.h"


class Hook : public Body2D
{
public:
	Hook();

	void OnContactStart(b2Contact* contact, Body2D* bodyA, Body2D* bodyB) override;

private:

};
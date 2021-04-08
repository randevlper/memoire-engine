#pragma once
#include "Engine/Nodes/Body2D.h"


class Hook : public Body2D
{
public:
	Hook();

	void tick() override;

	void OnContactStart(Collision2D collision) override;

private:

};
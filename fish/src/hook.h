#pragma once
#include "Engine/Physics2D/Body2D.h"


class Hook : public Body2D
{
public:
	Hook();

	void tick() override;

	void OnContactStart(Collision2D collision) override;

private:

};
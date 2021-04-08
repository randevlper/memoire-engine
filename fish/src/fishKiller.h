#pragma once
#include "Engine/Physics2D/Body2D.h"

class FishKiller : public Body2D
{
public:
	FishKiller();

	void OnContactStart(Collision2D collision) override;

private:

};
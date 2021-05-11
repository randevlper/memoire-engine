#pragma once
#include "Engine/Physics2D/Body2D.h"

class Obstacle : public Body2D {
public:

	void OnContactStart(Collision2D collision) override;
private:
};
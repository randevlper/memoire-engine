#pragma once
#include "Engine/Physics2D/Body2D.h"

class Hook : public Body2D
{
public:
	Hook();

	void init() override;
	void OnContactStart(Collision2D collision) override;

private:
};
#pragma once
#include "Engine/Physics2D/Body2D.h"

#define MAX_HOOKED_FISH 5

class Hook : public Body2D
{
public:
	Hook();

	void init() override;
	void OnContactStart(Collision2D collision) override;

	void loseFish();

	bool getCanCatch();
	void setCanCatch(bool value);

private:
	bool _canCatch;
};
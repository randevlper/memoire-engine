#pragma once
#include "Engine/Physics2D/Body2D.h"

class SpriteRenderer;

class Obstacle : public Body2D {
public:
	Obstacle();

	void init() override;
	void destroy() override;

	void OnContactStart(Collision2D collision) override;
private:
	SpriteRenderer* _spriteRenderer;
};
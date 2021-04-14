#pragma once
#include "Engine/Physics2D/Body2D.h"

class SpriteRenderer;

class Fish : public Body2D
{
public:
	Fish();

	void init() override;
	void destroy() override;

	int getScore() {
		return _score;
	}
	void setScore(int value) {
		_score = value;
	}

private:
	int _score;
	float _speed;
	SpriteRenderer* _spriteRenderer;
};

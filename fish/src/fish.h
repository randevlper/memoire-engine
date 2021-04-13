#pragma once
#include "Engine/Physics2D/Body2D.h"

class Fish : public Body2D
{
public:
	Fish();

	int getScore() {
		return _score;
	}
	void setScore(int value) {
		_score = value;
	}

private:
	int _score;
};

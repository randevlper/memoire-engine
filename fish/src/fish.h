#pragma once
#include "Engine/Nodes/Body2D.h"

class Fish : public Body2D
{
public:
	Fish();

private:

};

Fish::Fish()
{
	_type = "Fish";
}
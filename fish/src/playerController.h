#pragma once
#include "Engine/Nodes/Node2D.h"

class SpriteRenderer;
class Hook;
class Net;
class Fish;

class PlayerController : public Node2D
{
public:
	PlayerController();
	void init() override;

	void OnNetCatch(std::vector<Fish*> fishes);

private:
	SpriteRenderer* _spriteRenderer;
	Hook* _hook;
	Net* _net;
};
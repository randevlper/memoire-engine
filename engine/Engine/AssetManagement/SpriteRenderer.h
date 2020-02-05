#pragma once
#include "Engine/Nodes/Node.h"
class Sprite;

class SpriteRenderer : public Node
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void setSprite(Sprite* sprite);
	Sprite* getSprite();
	void render();

private:
	Sprite* _sprite;
};
#pragma once
#include "Engine/Nodes/Node2D.h"

class SpriteRenderer;
class Hook;
class Net;
class Fish;

namespace me {
	namespace ui {
		class Text;
	}
}

enum class PlayerState
{
	FISHING,
	CATCHING
};

class PlayerController : public Node2D
{
public:
	PlayerController();
	void init() override;
	void tick() override;

	void OnNetCatch(std::vector<Fish*> fishes);

	void fishing();
	void catching();

private:
	PlayerState _state;
	
	float _horizontalSpeed;
	float _minXPos;
	float _maxXPos;

	float _hookVerticalSpeed;
	float _hookAutoReal;
	float _hookMaxHeight;
	float _hookMaxDepth;

	me::ui::Text* _scoreText;
	int _score;

	SpriteRenderer* _spriteRenderer;
	Hook* _hook;
	Net* _net;

	SpriteRenderer* _buttonPressBackground;
	me::ui::Text* _buttonTextPromt;

	std::vector<Fish*> _fishToCatch;
	unsigned int _fishCatching;
};
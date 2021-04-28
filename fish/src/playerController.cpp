#include "playerController.h"

#include <SDL_keycode.h>

#include "Engine/Core/Context.h"
#include "Engine/Core/World.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Core/Input.h"

#include "Engine/UI/Text.h"

#include "net.h"
#include "hook.h"
#include "fish.h"

PlayerController::PlayerController()
{
	_type = "PlayerController";
	_net = nullptr;
	_hook = nullptr;
	_spriteRenderer = nullptr;

	_horizontalSpeed = 400;
	_hookVerticalSpeed = 500;
	_hookAutoReal = 100;

	_minXPos = -940;
	_maxXPos = 940;

	_hookMaxHeight = 400;
	_hookMaxDepth = -400;

	_score = 0;
	_scoreText = nullptr;
}

void PlayerController::init() {
	World* world = me::WorldManager::getWorld();
	_net = world->get<Net>("PlayerNet");
	_hook = world->get<Hook>("PlayerHook");

	_scoreText = world->get<me::ui::Text>("ScoreText");
	_scoreText->setText("Score: 0");

	if (_net) {
		_net->CaughtFish = std::bind(&PlayerController::OnNetCatch, this, std::placeholders::_1);
	}
}

void PlayerController::tick()
{
	float delta = Context::getDeltaTime();

	glm::vec2 dir = { 0,0 };
	if (Input::getKey(SDL_SCANCODE_LEFT)) {
		dir.x += -1;
	}
	if (Input::getKey(SDL_SCANCODE_RIGHT)) {
		dir.x += 1;
	}
	if (Input::getKey(SDL_SCANCODE_UP)) {
		dir.y += 1;
	}
	if (Input::getKey(SDL_SCANCODE_DOWN)) {
		dir.y += -1;
	}

	float horizontalMovement = dir.x * _horizontalSpeed;

	if (_transform.getLocalPosition().x > _maxXPos && horizontalMovement > 0) {
		horizontalMovement = 0;
	}
	if (_transform.getLocalPosition().x < _minXPos && horizontalMovement < 0) {
		horizontalMovement = 0;
	}

	_transform.translate({ horizontalMovement * delta,0 });
	//TODO Properly implement syncronization of Transform2D and Body2D
	_net->setVelocity({ horizontalMovement, 0 });

	float hookMovement = (_hookAutoReal + _hookVerticalSpeed) * dir.y;
	//Out of bounds and trying to go up
	if (_hook->getPosition().y > _hookMaxHeight && hookMovement > 0) {
		hookMovement = 0;
	}
	//Out of bounds and trying to go down
	if (_hook->getPosition().y < _hookMaxDepth && hookMovement < 0) {
		hookMovement = 0;
	}

	_hook->setVelocity({ dir.x * _horizontalSpeed, hookMovement });
	//Move hook up and down, move everything side to side
	//setVelocity(dir);
}


//If catch any fish, stop movement and pop up the input promts
void PlayerController::OnNetCatch(std::vector<Fish*> fishes)
{
	World* world = me::WorldManager::getWorld();
	for (size_t i = 0; i < fishes.size(); i++)
	{
		_score += fishes[i]->getScore();
		_scoreText->setText("Score: " + std::to_string(_score));
		world->destroy(fishes[i]);
	}
}

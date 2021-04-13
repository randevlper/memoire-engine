#include "hook.h"
#include <box2d/b2_contact.h>
#include "Engine/Core/Context.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

#include "Engine/UI/Text.h"

#include "fish.h"

#include "Engine/Core/Input.h"
#include <SDL_keycode.h>

Hook::Hook()
{
	_type = "Hook";
	_score = 0;
	_scoreText = nullptr;
}

void Hook::init()
{
	World* world = me::WorldManager::getWorld();
	_scoreText = world->get<me::ui::Text>("ScoreText");
}

void Hook::tick()
{
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
	dir *= Context::getDeltaTime() * 500;
	setVelocity(dir);
}

void Hook::OnContactStart(Collision2D collision)
{
	if (collision.other != nullptr) {
		if ("Fish" == collision.other->getType()) {
			World* world = me::WorldManager::getWorld();
			if (world != nullptr) {
				world->destroy(collision.other);
			}

			Fish* fish = dynamic_cast<Fish*>(collision.other);
			_score += fish->getScore();
			_scoreText->setText("Score: " + std::to_string(_score));
		}
	}
}
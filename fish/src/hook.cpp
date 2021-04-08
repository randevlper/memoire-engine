#include "hook.h"
#include <box2d/b2_contact.h>
#include "Engine/Utilities/Debug.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

#include "Engine/Core/Input.h"
#include <SDL_keycode.h>

Hook::Hook()
{
	_type = "Hook";
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
	dir *= 10;
	setVelocity(dir);
}

void Hook::OnContactStart(Collision2D collision)
{
	if (collision.other != nullptr) {
		if ("Fish" == collision.other->getType()) {
			Debug::Log("Caught Fish!");
			World* world = me::WorldManager::getWorld();

			if (world != nullptr) {
				world->destroy(collision.other);
			}
		}
	}
}
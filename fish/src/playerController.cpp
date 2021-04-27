#include "playerController.h"

#include "Engine/Core/World.h"
#include "Engine/Core/WorldManager.h"

#include "Engine/Nodes/SpriteRenderer.h"

#include "Engine/Utilities/Debug.h"

#include "net.h"
#include "hook.h"
#include "fish.h"

PlayerController::PlayerController()
{
	_type = "PlayerController";
	_net = nullptr;
	_hook = nullptr;
	_spriteRenderer = nullptr;
}

void PlayerController::init() {
	World* world = me::WorldManager::getWorld();
	_net = world->get<Net>("PlayerNet");
	_hook = world->get<Hook>("PlayerHook");

	if (_net) {
		_net->CaughtFish = std::bind(&PlayerController::OnNetCatch, this, std::placeholders::_1);
	}
}

void PlayerController::OnNetCatch(std::vector<Fish*> fishes)
{
	World* world = me::WorldManager::getWorld();
	for (size_t i = 0; i < fishes.size(); i++)
	{
		world->destroy(fishes[i]);
	}
}

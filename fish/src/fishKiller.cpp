#include "fishKiller.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

FishKiller::FishKiller()
{
	_type = "FishKiller";
}

void FishKiller::OnContactStart(Collision2D collision)
{
	if (collision.other != nullptr) {
		if ("Fish" == collision.other->getType() || "Obstacle" == collision.other->getType()) {
			//Debug::Log("Caught Fish!");
			World* world = me::WorldManager::getWorld();

			if (world != nullptr) {
				world->destroy(collision.other);
			}
		}
	}
}

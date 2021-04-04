#include "fishKiller.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

FishKiller::FishKiller()
{
	_type = "FishKiller";
}

void FishKiller::OnContactStart(b2Contact* contact, Body2D* bodyA, Body2D* bodyB)
{
	Body2D* other = nullptr;
	if (bodyA != this) {
		other = bodyA;
	}
	else if (bodyB != this) {
		other = bodyB;
	}
	if (other != nullptr) {
		if ("Fish" == other->getType()) {
			Debug::Log("Caught Fish!");
			World* world = me::WorldManager::getWorld();

			if (world != nullptr) {
				world->destroy(other);
			}
		}
	}
}

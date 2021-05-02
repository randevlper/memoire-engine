#include "hook.h"
#include <box2d/b2_contact.h>
#include "Engine/Utilities/Debug.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

#include "fish.h"
#include "collision.h"

Hook::Hook()
{
	_type = "Hook";
}

void Hook::init()
{
	setupBox(0, 0, 50, 50, Body2DType::Kinematic, CollisionCatagories::HOOK,
		CollisionCatagories::FISH | CollisionCatagories::NET, true);
}

void Hook::OnContactStart(Collision2D collision)
{
	if (collision.other != nullptr) {
		if ("Fish" == collision.other->getType()) {
			if (_transform.getChildren().size() >= MAX_HOOKED_FISH) { return; }
			Fish* fish = dynamic_cast<Fish*>(collision.other);
			
			if (!fish->isAwake()) { return; }

			glm::vec2 pos = fish->getPosition();
			Transform t = fish->getTransform();
			t.setParent(this);
			t.setPosition(pos);
			fish->setTransform(t);
			fish->setIsAwake(false);
		}
	}
}
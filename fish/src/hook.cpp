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
	_canCatch = true;
}

void Hook::init()
{
	setupBox(0, 0, 50, 50, Body2DType::Kinematic, CollisionCatagories::HOOK,
		CollisionCatagories::FISH | CollisionCatagories::NET, true);
}

void Hook::OnContactStart(Collision2D collision)
{
	if (collision.other != nullptr && _canCatch) {
		if ("Fish" == collision.other->getType()) {
			if (_transform.getChildren().size() >= MAX_HOOKED_FISH) { return; }
			Fish* fish = dynamic_cast<Fish*>(collision.other);
			if (!fish->isAwake()) { return; }
			fish->attach(this);
		}
	}
}

void Hook::loseFish()
{
	std::vector<Node2D*> nodes = _transform.getChildren();
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->getType() == "Fish") {
			Fish* fish = dynamic_cast<Fish*>(nodes[i]);
			fish->disconnect();
		}
	}
}

bool Hook::getCanCatch()
{
	return _canCatch;
}

void Hook::setCanCatch(bool value)
{
	_canCatch = value;
}

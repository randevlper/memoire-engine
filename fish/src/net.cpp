#include "net.h"
#include "Engine/Utilities/Debug.h"
#include "collision.h"
#include "fish.h"

Net::Net()
{
	_type = "Net";
}

void Net::init()
{
	setupBox(0, 400, 200, 50, Body2DType::Dynamic, CollisionCatagories::NET,
		CollisionCatagories::HOOK, true);
}

void Net::OnContactStart(Collision2D collision)
{
	if (collision.other->getType() == "Hook") {
		if (CaughtFish) {
			std::vector<Node2D*> nodes = collision.other->getTransform().getChildren();
			std::vector<Fish*> fish;
			for (size_t i = 0; i < nodes.size(); i++)
			{
				if (nodes[i]->getType() == "Fish") {
					Fish* f = dynamic_cast<Fish*>(nodes[i]);
					fish.push_back(f);
				}
			}

			if (fish.size() > 0) {
				CaughtFish(fish);
			}
		}
	}
}

#include "fish.h"
#include <box2d/b2_contact.h>
#include "Engine/Utilities/Debug.h"

Fish::Fish()
{
	_type = "Fish";
}

void Fish::setVelocity(glm::vec2 value)
{
	_body->SetLinearVelocity({ value.x, value.y });
}

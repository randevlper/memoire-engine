#include "ObjectFactory.h"

#include "Engine/UI/NodeUI.h"
#include "Engine/UI/Text.h"
#include "Engine/UI/Button.h"

#include "Engine/Nodes/Node2D.h"
#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/Nodes/Camera.h"

#include "Engine/Nodes/Body2D.h"

namespace me {
	namespace util {
		nodeMapType ObjectFactory::nodeMap = nodeMapType();

		void ObjectFactory::init()
		{
			nodeMap["Node"] = createInstance<Node>;
			nodeMap["Node2D"] = createInstance<Node2D>;
			nodeMap["NodeUI"] = createInstance<NodeUI>;

			//Node2D
			nodeMap["Camera"] = createInstance<Camera>;
			nodeMap["SpriteRenderer"] = createInstance<SpriteRenderer>;

			nodeMap["Body2D"] = createInstance<Body2D>;

			//UI
			nodeMap["Text"] = createInstance<me::ui::Text>;
			nodeMap["Button"] = createInstance<me::ui::Button>;
		}

		void ObjectFactory::destroy()
		{
		}

		Node* ObjectFactory::createObject(std::string const& s)
		{
			nodeMapType::iterator it = nodeMap.find(s);
			if (it == nodeMap.end()) {
				throw s + "Does not exist in ObjectFactory nodeMap!";
				return nullptr;
			}
			return it->second();
		}
	}
}



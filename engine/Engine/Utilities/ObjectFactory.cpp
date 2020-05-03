#include "ObjectFactory.h"

#include "Engine/UI/NodeUI.h"

#include "Engine/UI/Text.h"
#include "Engine/UI/Button.h"

#include "Engine/Nodes/Node2D.h"

namespace me {
	namespace util {
		nodeMapType ObjectFactory::nodeMap = nodeMapType();

		void ObjectFactory::init()
		{
			nodeMap["Node"] = createInstance<Node>;
			nodeMap["Node2D"] = createInstance<Node2D>;
			nodeMap["NodeUI"] = createInstance<NodeUI>;

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
				return nullptr;
			}
			return it->second();
		}
	}
}



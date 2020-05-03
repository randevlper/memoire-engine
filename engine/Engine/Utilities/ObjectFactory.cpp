#include "ObjectFactory.h"

#include "Engine/UI/Text.h"

namespace me {
	namespace util {
		nodeMapType ObjectFactory::nodeMap = nodeMapType();

		void ObjectFactory::init()
		{
			nodeMap["Node"] = createInstance<Node>;

			//UI
			nodeMap["Text"] = createInstance<me::ui::Text>;
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



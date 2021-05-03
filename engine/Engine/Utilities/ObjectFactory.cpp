#include "ObjectFactory.h"

#include "Engine/UI/NodeUI.h"
#include "Engine/UI/Text.h"
#include "Engine/UI/Button.h"
#include "Engine/UI/Image.h"

#include "Engine/Nodes/Node2D.h"
#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/Nodes/Camera.h"

#include "Engine/Physics2D/Body2D.h"

using namespace me::ui;

namespace me {
	namespace util {
		nodeMapType ObjectFactory::nodeMap = nodeMapType();

		void ObjectFactory::init()
		{
			ADD_OBJECT_MAP(Node)
			ADD_OBJECT_MAP(Node2D)
			ADD_OBJECT_MAP(NodeUI)

			//Node2D
			ADD_OBJECT_MAP(Camera)
			ADD_OBJECT_MAP(SpriteRenderer)
			ADD_OBJECT_MAP(Body2D)

			//UI
			ADD_OBJECT_MAP(Text)
			ADD_OBJECT_MAP(Button)
			ADD_OBJECT_MAP(Image);
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



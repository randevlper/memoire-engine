#pragma once
#include <functional>
#include <string>
class Node;

namespace me {
	namespace imgui {
		namespace worldEditor {
			void showEditor();
			void addNodeEditor(std::string nodeName, std::function<void(Node*)> node);
		}
	}
}
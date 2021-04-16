#pragma once
#include <functional>
#include <string>
class Node;

namespace me {
	namespace imgui {
		namespace worldEditor {
			void showEditor();

			void addNodeEditor(std::string nodeName, std::function<void(Node*)> node);

			void editorNode2D(Node* node);
			void editorSpriteRenderer(Node* node);
			void editorCamera(Node* node);
			void editorBody2D(Node* node);
		}
	}
}
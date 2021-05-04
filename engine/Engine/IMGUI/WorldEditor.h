#pragma once
#include <functional>
#include <string>
class Node;
class Sprite;

namespace me {
	namespace imgui {
		namespace worldEditor {
			void showEditor();

			void addNodeEditor(std::string nodeName, std::function<void(Node*)> node);

			Sprite* loadSpriteWindow(Sprite* currentSprite);

			void editorNode2D(Node* node);
			void editorSpriteRenderer(Node* node);
			void editorCamera(Node* node);
			void editorBody2D(Node* node);

			void editorNodeUI(Node* node);
			void editorButton(Node* node);
			void editorText(Node* node);
			void editorImage(Node* node);
		}
	}
}
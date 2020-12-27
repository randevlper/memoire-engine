#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class SpriteRenderer;
namespace me {
	namespace ui {
		class Text;
	}
}

namespace lb {

	class Dialogue;
	struct Character;

	//Become a Node so the World can load it in when it starts
	class DialogueWriter
	{
	public:
		static void tick(float deltaTime);
		static void startDialouge(Dialogue* dia);
		static void progress();


		static void clear();
		static void setTextBox(me::ui::Text* textBox);
		static void addSpriteRenderer(SpriteRenderer* render);
	private:
		DialogueWriter() {};
		~DialogueWriter() {};

		static unsigned int _currentLine;
		static Dialogue* _dialogue;
		static std::vector<SpriteRenderer*> _sRenderers;
		static std::vector<Character> _characters;

		static me::ui::Text* _textBox;

	};
}
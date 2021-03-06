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
		static void init();
		static void tick(float deltaTime);
		static void startDialouge(Dialogue* dia);
		static void progress();


		static void clear();
		static void setTextBox(me::ui::Text* textBox, me::ui::Text* nameplate);
		static void addSpriteRenderer(SpriteRenderer* render);

		static std::vector<Character> getCharacters();
		static void setCharacters(std::vector<Character> characters);

	private:
		DialogueWriter() {};
		~DialogueWriter() {};

		static unsigned int _currentLine;
		static Dialogue* _dialogue;
		static std::vector<SpriteRenderer*> _sRenderers;
		static std::vector<Character> _characters;

		static me::ui::Text* _textBox;
		static me::ui::Text* _nameplate;

	};
}
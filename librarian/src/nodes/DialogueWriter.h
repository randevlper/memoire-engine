#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>


namespace me {
	namespace ui {
		class Text;
	}
}

namespace lb {

	class Dialogue;

	//Become a Node so the World can load it in when it starts
	class DialogueWriter
	{
	public:
		static void tick(float deltaTime);
		static void startDialouge(Dialogue* dia);
		static void progress();


		static void setTextBox(me::ui::Text* textBox);
	private:
		DialogueWriter() {};
		~DialogueWriter() {};

		static unsigned int _currentLine;
		static Dialogue* _dialogue;

		static me::ui::Text* _textBox;

	};
}
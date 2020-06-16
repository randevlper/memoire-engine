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
		DialogueWriter();
		~DialogueWriter();

		void tick(float deltaTime);
		void startDialouge(Dialogue* dia);
		void progress();


		void setTextBox(me::ui::Text* textBox);
	private:
		unsigned int _currentLine;
		Dialogue* _dialogue;

		me::ui::Text* _textBox;

	};
}
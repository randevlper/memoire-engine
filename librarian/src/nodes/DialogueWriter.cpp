#include "DialogueWriter.h"
#include "Engine/UI/Text.h"
#include "Engine/Utilities/Debug.h"

#include "assetmanagement/Dialogue.h"

namespace lb {
	unsigned int DialogueWriter::_currentLine = 0;
	Dialogue* DialogueWriter::_dialogue = nullptr;
	me::ui::Text* DialogueWriter::_textBox = nullptr;

	void DialogueWriter::tick(float deltaTime)
	{

	}

	void DialogueWriter::startDialouge(Dialogue* dia)
	{
		if (dia == nullptr) { Debug::Log("[DialogueWriter] Dialouge is nullptr!"); return; }
		_dialogue = dia;
		_currentLine = 0;
		progress();
	}

	void DialogueWriter::progress()
	{
		//Bulk of the code
		//Click, set the dialogue
		if (_dialogue == nullptr) { Debug::Log("[DialogueWriter] Has no dialogue!"); return; }
		if(_textBox == nullptr) { Debug::Log("[DialogueWriter] Has no text box!"); return; }

		if (_currentLine >= _dialogue->lines.size()) { 
			_textBox->setText("END TEXT"); 
			_dialogue = nullptr;
			return;
		}

		_textBox->setText(_dialogue->lines[_currentLine].text);
		_currentLine++;
	}

	void DialogueWriter::setTextBox(me::ui::Text* textBox)
	{
		_textBox = textBox;
	}
}
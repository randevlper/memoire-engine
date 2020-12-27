#include "DialogueWriter.h"
#include "Engine/UI/Text.h"
#include "Engine/Utilities/Debug.h"

#include "Engine/Nodes/SpriteRenderer.h"
#include "assetmanagement/Dialogue.h"

namespace lb {
	unsigned int DialogueWriter::_currentLine = 0;
	Dialogue* DialogueWriter::_dialogue = nullptr;
	me::ui::Text* DialogueWriter::_textBox = nullptr;
	std::vector<SpriteRenderer*> DialogueWriter::_sRenderers = std::vector<SpriteRenderer*>();

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

		bool doProgress = false;

		switch (_dialogue->lines[_currentLine].characterCommand)
		{
		case DialogueLine::CharacterCommand::SAY:
			_textBox->setText(_dialogue->lines[_currentLine].value);
			break;
		case DialogueLine::CharacterCommand::SPRITE:
			doProgress = true;
			break;
		default:
			break;
		}

		
		_currentLine++;

		if (doProgress) {
			progress();
		}
	}

	void DialogueWriter::clear()
	{
		_sRenderers = std::vector<SpriteRenderer*>();
		_textBox = nullptr;
	}

	void DialogueWriter::setTextBox(me::ui::Text* textBox)
	{
		_textBox = textBox;
	}

	void DialogueWriter::addSpriteRenderer(SpriteRenderer* render)
	{
		if (render == nullptr) { return; }
		_sRenderers.push_back(render);
	}
}
#include "DialogueWriter.h"
#include "Engine/UI/Text.h"
#include "Engine/Utilities/Debug.h"

#include "Engine/Nodes/SpriteRenderer.h"
#include "assetmanagement/Dialogue.h"

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Sprite.h"

#include "Engine/Core/FileUtility.h"

namespace lb {
	unsigned int DialogueWriter::_currentLine = 0;
	Dialogue* DialogueWriter::_dialogue = nullptr;
	me::ui::Text* DialogueWriter::_textBox = nullptr;
	me::ui::Text* DialogueWriter::_nameplate = nullptr;
	std::vector<SpriteRenderer*> DialogueWriter::_sRenderers = std::vector<SpriteRenderer*>();
	std::vector<Character> DialogueWriter::_characters = std::vector<Character>();

	void DialogueWriter::init()
	{
		nlohmann::json j;
		std::string filepath = CHARACTER_PATH;
		filepath += CHARACTER_FILE;
		FileUtility::loadJson(filepath.c_str(), j);

		std::vector<Character> characters;
		for each (nlohmann::json item in j)
		{
			Character c;
			c.from_json(item);
			characters.push_back(c);
		}
		DialogueWriter::setCharacters(characters);
	}

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
		std::string path;
		Character character;
		Sprite* s = nullptr;

		switch (_dialogue->lines[_currentLine].characterCommand)
		{
		case DialogueLine::CharacterCommand::SAY:
			_nameplate->setText(_dialogue->lines[_currentLine].character);
			_textBox->setText(_dialogue->lines[_currentLine].value);
			break;
		case DialogueLine::CharacterCommand::SPRITE:
			for each (Character item in _characters)
			{
				if (item.name == _dialogue->lines[_currentLine].character) {
					character = item;
				}
			}
			path += character.sprites;
			path += _dialogue->lines[_currentLine].value;
			s = AssetManager::getLoad<Sprite>(path, "");
			_sRenderers[0]->setSprite(s);
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
		//_characters = std::vector<Character>(); //TODO Unload character sprites here
		_textBox = nullptr;
	}

	void DialogueWriter::setTextBox(me::ui::Text* textBox, me::ui::Text* nameplate)
	{
		_textBox = textBox;
		_nameplate = nameplate;
	}

	void DialogueWriter::addSpriteRenderer(SpriteRenderer* render)
	{
		if (render == nullptr) { return; }
		_sRenderers.push_back(render);
	}
	std::vector<Character> DialogueWriter::getCharacters()
	{
		return _characters;
	}
	void DialogueWriter::setCharacters(std::vector<Character> characters)
	{
		_characters = characters;
	}
}
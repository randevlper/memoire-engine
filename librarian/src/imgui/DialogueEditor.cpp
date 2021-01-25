#include "DialogueEditor.h"

#include <vector>
#include <string>
#include <filesystem>

#include <dear-imgui/imgui.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/UI/Text.h"

#include "Engine/Utilities/DebugMemory.h"

#include "imgui/ImguiUtilities.h"
#include "Engine/thirdparty/imgui/imgui_stdlib.h"

#include "nodes/DialogueWriter.h"
#include "assetmanagement/Dialogue.h"

#define DIALOGUE_PATH "assets/dialogue/"

namespace lb {
	namespace imgui {
		namespace dialogueEditor {

			static bool d_open = false;
			static Dialogue* dialogue = DBG_NEW Dialogue();
			static bool isPreview = false;
			static DialogueWriter* dialogueWriter = nullptr;

			static bool isFileLoadSelectOpen = false;
			static std::filesystem::directory_entry fileLoadSelectEntry = std::filesystem::directory_entry();

			const char* characterCommands[3] = { "SAY", "SPRITE", "SOUND" };

			

			static bool c_open = false;
			static int characterSelected = 0;

			void save() {
				std::string filename = dialogue->name + DIALOGUE_FILE_TYPE;
				dialogue->path = DIALOGUE_PATH + filename;
				FileUtility::writeStringFile(DIALOGUE_PATH, filename.c_str(), dialogue->to_json().dump(4));
			}

			void preview() {
				if (dialogueWriter != nullptr) {
					dialogueWriter->startDialouge(dialogue);
				}
			}

			void init(DialogueWriter* writer)
			{
				dialogueWriter = writer;
			}

			void characterLoad() {
				DialogueWriter::init();
			}

			void characterSave() {
				nlohmann::json j;
				for each (Character character in DialogueWriter::getCharacters())
				{
					j.push_back(character.to_json());
				}
				FileUtility::writeStringFile(CHARACTER_PATH, CHARACTER_FILE, j.dump(4));
				DialogueWriter::init();
			}

			void showEditor()
			{

				std::string file = lb::imgui::utilities::selectFile(isFileLoadSelectOpen, fileLoadSelectEntry, DIALOGUE_PATH, DIALOGUE_FILE_TYPE);
				if (file != "null") {
					file += DIALOGUE_FILE_TYPE;
					AssetManager::load(file, "");
					Dialogue* d = AssetManager::get<Dialogue>(file);
					if (d != nullptr) {
						dialogue = d;
					}
					isFileLoadSelectOpen = false;
				}

				if (ImGui::BeginMainMenuBar()) {
					if (ImGui::BeginMenu("Tools"))
					{
						if (ImGui::MenuItem("Open Dialogue Editor")) { d_open = true; }
						ImGui::EndMenu();
					}
					ImGui::EndMainMenuBar();
				}

				if (c_open) {
					ImGui::Begin("Characters###d_character_editor", &c_open, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar()) {
						if (ImGui::BeginMenu("File###d_character_editor_menu"))
						{
							if (ImGui::MenuItem("Save###d_character_editor_save", "Ctrl+S")) { characterSave(); }
							if (ImGui::MenuItem("Load###d_character_editor_load", "Ctrl+L")) { characterLoad(); }
							if (ImGui::MenuItem("Close###d_character_editor_close", "Ctrl+W")) { c_open = false; }
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();
					}

					std::vector<Character> characters = DialogueWriter::getCharacters();
					if (characterSelected >= characters.size()) {
						characterSelected = 0;
					}


					if (ImGui::Button("+", ImVec2(25, 25))) {
						std::string newText = "NewCharacter_" + std::to_string(characters.size());
						for (size_t i = 0; i < characters.size(); i++)
						{
							if (characters[i].name == newText) {
								newText += "0";
							}
						}

						lb::Character charat;
						charat.name = newText;
						characters.push_back(charat);
					}

					ImGui::BeginChild("Characters List###c_characters", ImVec2(150, 0), true);
					for (size_t i = 0; i < characters.size(); i++){
						if (ImGui::Selectable(characters[i].name.c_str(), characterSelected == i)) {
							characterSelected = i;
						}
					}
					ImGui::EndChild();

					if (characters.size() > 0) {
						ImGui::SameLine();
						ImGui::BeginGroup();
						ImGui::InputText("Name###c_Character_Name", &characters[characterSelected].name);
						ImGui::InputText("Sprites Path###c_Character_Path", &characters[characterSelected].sprites);
						ImGui::EndGroup();
					}
					DialogueWriter::setCharacters(characters);

					ImGui::End();
				}


				if (d_open) {
					ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
					ImGui::Begin("Dialogue Editor", &d_open, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar()) {

						if (ImGui::BeginMenu("File"))
						{
							if (ImGui::MenuItem("Open..", "Ctrl+O")) { isFileLoadSelectOpen = true; }
							if (ImGui::MenuItem("Save", "Ctrl+S")) { save(); }
							if (ImGui::MenuItem("Close", "Ctrl+W")) { d_open = false; }
							if (ImGui::MenuItem("New", "Ctrl+N")) { 
								//TODO This will create garbage - but right now i dont care
								dialogue = DBG_NEW Dialogue(); }
							if (ImGui::MenuItem("Start Preview")) { preview(); }
							ImGui::EndMenu();
						}

						if (ImGui::MenuItem("Characters###dialogue_editor_characters")) {
							c_open = true;
						}

						ImGui::EndMenuBar();
					}

					static int selected = 0;
					ImGui::Text(dialogue->path.c_str());
					ImGui::InputText("Name###DialogueName", &dialogue->name);
					ImGui::Text("Lines");
					ImGui::Checkbox("Preview", &isPreview);

					if (ImGui::Button("+", ImVec2(25, 25))) {
						std::string newText = "NewItem_" + std::to_string(dialogue->lines.size());
						for (size_t i = 0; i < dialogue->lines.size(); i++)
						{
							if (dialogue->lines[i].name == newText) {
								newText += "0";
							}
						}

						DialogueLine newLine(newText, "New");
						dialogue->lines.push_back(newLine);
					}

					ImGui::SameLine();
					if (ImGui::Button("-", ImVec2(25, 25))) {
						if (selected < dialogue->lines.size()) {
							dialogue->lines.erase(dialogue->lines.begin() + selected);
							selected--;
							if (selected < 0) {
								selected = 0;
							}
						}
					}

					if (ImGui::Button("/\\", ImVec2(25, 25))) {
						//Check where the element is at and attemt to move it above
						int spot = selected - 1;
						if (spot < 0) { spot = 0; };
						std::vector<DialogueLine>::iterator it = dialogue->lines.begin() + spot;
						dialogue->lines.insert(it, dialogue->lines[selected]);

						it = dialogue->lines.begin() + selected + 1;
						dialogue->lines.erase(it);

						if (spot != 0) {
							selected -= 1;
						}
						else {
							selected = 0;
						}
					}

					ImGui::SameLine();
					if (ImGui::Button("\\/", ImVec2(25, 25))) {
						//Check where the element is at and attemt to move it below
						int spot = selected + 2;
						if (spot >= dialogue->lines.size()) {
							dialogue->lines.push_back(dialogue->lines[selected]);
							std::vector<DialogueLine>::iterator it = dialogue->lines.begin() + selected;
							dialogue->lines.erase(it);

							selected = dialogue->lines.size() - 1;

						}
						else {
							std::vector<DialogueLine>::iterator it = dialogue->lines.begin() + spot;
							dialogue->lines.insert(it, dialogue->lines[selected]);

							it = dialogue->lines.begin() + selected;
							dialogue->lines.erase(it);

							selected += 1;
						}
					}

					ImGui::BeginChild("line view", ImVec2(150, 0), true);
					for (size_t i = 0; i < dialogue->lines.size(); i++)
					{
						if (ImGui::Selectable(dialogue->lines[i].name.c_str(), selected == i)) {
							selected = i;
							if (isPreview) {
								//if (text != nullptr) {
								//	text->setText(dialogue->lines[i].text);
								//}
							}
						}
					}
					ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginGroup();
					if (dialogue->lines.size() > 0) {
						
						static std::vector<Character> characters = DialogueWriter::getCharacters();

						ImGui::InputText("dialogue_name", &dialogue->lines[selected].name, ImGuiInputTextFlags_CharsNoBlank);
						
						//ImGui::InputText("dialogue_character", &dialogue->lines[selected].character, ImGuiInputTextFlags_CharsNoBlank);

						const char* selectedCharacter = dialogue->lines[selected].character.c_str();
						if (ImGui::BeginCombo("###dialogue_character_name", selectedCharacter)) {
							for (size_t i = 0; i < characters.size(); i++)
							{
								const char* character_cstring = characters[i].name.c_str();
								bool is_selected = selectedCharacter == character_cstring;
								if (ImGui::Selectable(character_cstring, is_selected)) {
									dialogue->lines[selected].character = character_cstring;
								}
								if (is_selected) {
									ImGui::SetItemDefaultFocus();
								}
							}
							ImGui::EndCombo();
						}
						
						const char* selectedCharacterCommand = characterCommands[dialogue->lines[selected].characterCommand];
						if (ImGui::BeginCombo("###dialogue_character_command", selectedCharacterCommand)) {
							for (int i = 0; i < IM_ARRAYSIZE(characterCommands); i++) {
								bool is_selected = (selectedCharacterCommand == characterCommands[i]);
								if (ImGui::Selectable(characterCommands[i], is_selected)) {
									dialogue->lines[selected].characterCommand = (DialogueLine::CharacterCommand)i;
								}
								if (is_selected) {
									ImGui::SetItemDefaultFocus();
								}
							}
							ImGui::EndCombo();
						}
						
						switch (dialogue->lines[selected].characterCommand)
						{
						case DialogueLine::CharacterCommand::SAY:
							ImGui::InputTextMultiline("dialogue_value", &dialogue->lines[selected].value);
							break;
						case DialogueLine::CharacterCommand::SPRITE:
							ImGui::InputText("dialogue_value", &dialogue->lines[selected].value);
							break;
						case DialogueLine::CharacterCommand::SOUND:
							ImGui::InputText("dialogue_value", &dialogue->lines[selected].value);
							break;
						default:
							break;
						}
						
					}
					ImGui::EndGroup();

					ImGui::End();
				}
			}
		}
	}
}

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

			const char* characterCommands[2] = { "SAY", "SPRITE" };

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

				if (d_open) {
					ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
					ImGui::Begin("Dialogue Editor", &d_open, ImGuiWindowFlags_MenuBar);
					if (ImGui::BeginMenuBar()) {

						if (ImGui::BeginMenu("File"))
						{
							if (ImGui::MenuItem("Open..", "Ctrl+O")) { isFileLoadSelectOpen = true; }
							if (ImGui::MenuItem("Save", "Ctrl+S")) { save(); }
							if (ImGui::MenuItem("Close", "Ctrl+W")) { d_open = false; }
							if (ImGui::MenuItem("Start Preview")) { preview(); }
							ImGui::EndMenu();
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
						

						ImGui::InputText("dialogue_name", &dialogue->lines[selected].name, ImGuiInputTextFlags_CharsNoBlank);
						
						ImGui::InputText("dialogue_character", &dialogue->lines[selected].character, ImGuiInputTextFlags_CharsNoBlank);
						
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

						ImGui::InputTextMultiline("dialogue_value", &dialogue->lines[selected].value);
					}
					ImGui::EndGroup();

					ImGui::End();
				}
			}
		}
	}
}

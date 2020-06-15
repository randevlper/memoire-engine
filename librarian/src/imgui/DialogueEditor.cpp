#include "DialogueEditor.h"

#include <vector>
#include <string>

#include <dear-imgui/imgui.h>
#include <Engine/thirdparty/imgui/imgui_stdlib.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Engine/Core/FileUtility.h"
#include "Engine/UI/Text.h"
#include "../DialogueWriter.h"

namespace lb {
	namespace imgui {

		static bool d_open = false;
		static Dialogue dialogue;

		static bool isPreview = false;

		void save() {
			FileUtility::writeStringFile("dialogue/", "test.json", dialogue.to_json().dump(4));
		}

		void load() {
			json file;
			if (FileUtility::loadJson("dialogue/test.json", file)) {
				dialogue.from_json(file);
			}
		}

		void showDialogueEditor(me::ui::Text* text)
		{
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
						if (ImGui::MenuItem("Open..", "Ctrl+O")) { load(); }
						if (ImGui::MenuItem("Save", "Ctrl+S")) { save(); }
						if (ImGui::MenuItem("Close", "Ctrl+W")) { d_open = false; }
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}

				static int selected = 0;
				ImGui::Text("Lines");
				ImGui::Checkbox("Preview", &isPreview);

				if (ImGui::Button("+", ImVec2(25, 25))) {
					std::string newText = "NewItem_" + std::to_string(dialogue.lines.size());
					for (size_t i = 0; i < dialogue.lines.size(); i++)
					{
						if (dialogue.lines[i].name == newText) {
							newText += "0";
						}
					}

					DialogueLine newLine(newText, "New Text");
					dialogue.lines.push_back(newLine);
				}
				ImGui::SameLine();
				if (ImGui::Button("-", ImVec2(25,25))) {
					if (selected < dialogue.lines.size()) {
						dialogue.lines.erase(dialogue.lines.begin() + selected);
						selected--;
						if (selected < 0) {
							selected = 0;
						}
					}
				}

				
				ImGui::BeginChild("line view", ImVec2(150, 0), true);
				for (size_t i = 0; i < dialogue.lines.size(); i++)
				{
					if (ImGui::Selectable(dialogue.lines[i].name.c_str(), selected == i)) {
						selected = i;
						if (isPreview) {
							text->setText(dialogue.lines[i].text);
						}
					}
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginGroup();
				if (dialogue.lines.size() > 0) {
					ImGui::InputText("name", &dialogue.lines[selected].name, ImGuiInputTextFlags_CharsNoBlank);
					ImGui::InputTextMultiline("text", &dialogue.lines[selected].text);
				}
				ImGui::EndGroup();

				ImGui::End();
			}
		}
	}
}

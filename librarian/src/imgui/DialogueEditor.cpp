#include "DialogueEditor.h"

#include <vector>
#include <string>

#include <dear-imgui/imgui.h>
#include <Engine/thirdparty/imgui/imgui_stdlib.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Engine/Core/FileUtility.h"
#include "Engine/UI/Text.h"

namespace lb {
	namespace imgui {

		struct Item
		{
			std::string name;
			std::string text;

			Item(std::string n, std::string t) {
				name = n; text = t;
			}

			Item(json j) {
				from_json(j);
			}

			json to_json() {
				json retval;
				retval["name"] = name;
				retval["text"] = text;
				return retval;
			}
			void from_json(json j) {
				name = j["name"];
				text = j["text"];
			}
		};

		static bool d_open = false;
		static std::vector < Item> lines;

		static bool isPreview = false;

		void save() {
			json file;
			for (size_t i = 0; i < lines.size(); i++)
			{
				file["lines"][i] = lines[i].to_json();
			}

			FileUtility::writeStringFile("dialouge/", "test.json", file.dump(4));
		}

		void load() {
			json file;
			if (FileUtility::loadJson("dialouge/test.json", file)) {
				lines.clear();
				for (auto& [key, value] : file["lines"].items()) {
					Item newItem(value);
					lines.push_back(value);
				}
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
					std::string newText = "NewItem_" + std::to_string(lines.size());
					for (size_t i = 0; i < lines.size(); i++)
					{
						if (lines[i].name == newText) {
							newText += "0";
						}
					}

					lines.push_back({newText, "New Text" });
				}
				ImGui::SameLine();
				if (ImGui::Button("-", ImVec2(25,25))) {
					if (selected < lines.size()) {
						lines.erase(lines.begin() + selected);
						selected--;
						if (selected < 0) {
							selected = 0;
						}
					}
				}

				
				ImGui::BeginChild("line view", ImVec2(150, 0), true);
				for (size_t i = 0; i < lines.size(); i++)
				{
					if (ImGui::Selectable(lines[i].name.c_str(), selected == i)) {
						selected = i;
						if (isPreview) {
							text->setText(lines[i].text);
						}
					}
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginGroup();
				if (lines.size() > 0) {
					ImGui::InputText("name", &lines[selected].name, ImGuiInputTextFlags_CharsNoBlank);
					ImGui::InputTextMultiline("text", &lines[selected].text);
				}
				ImGui::EndGroup();

				ImGui::End();
			}
		}
	}
}

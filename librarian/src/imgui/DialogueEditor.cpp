#include "DialogueEditor.h"
#include "dear-imgui/imgui.h"

namespace lb {
	namespace imgui {
		static bool d_open = false;
		static char lineTest[64];
		void showDialogueEditor()
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
				ImGui::Begin("Dialogue Editor", &d_open, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar()) {

					if (ImGui::BeginMenu("File"))
					{
						if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
						if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
						if (ImGui::MenuItem("Close", "Ctrl+W")) { d_open = false; }
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}
				ImGui::Text("Lines");
				ImGui::Button("+");
				ImGui::InputText("Line", lineTest, 64);
				ImGui::End();
			}
		}
	}
}

#include "ImguiUtilities.h"

#include <dear-imgui/imgui.h>

std::string lb::imgui::utilities::selectFile(bool &isOpen, std::filesystem::directory_entry& directory, 
	 std::string folder, std::string fileExt)
{
	std::string retval = "null";
	if (isOpen) {
		ImGui::Begin("Seletct File###OpenSelectFileWindow", &isOpen);

		////List of loadable worlds
		if (ImGui::BeginChild("###LoadWorldWorlds", { 200, 250 }, true)) {
			//Should store the entries on opening the window
			for (const auto& entry : std::filesystem::directory_iterator(folder)) {
				if (entry.path().extension() != fileExt) { continue; }
				if (ImGui::Selectable(entry.path().filename().string().c_str(),
					directory.path().string().compare(entry.path().string()) == 0)) {
					directory = entry;
				}
			}
			ImGui::EndChild();
		}

		//Load button
		if (ImGui::Button("Load###LoadSelectedFile")) {
			if (directory.exists()) {
				//Should check if world has been saved and prompt with asking if it should be saved
				//ImGui::BeginPopupModal()
				std::ostringstream filestring;
				filestring << folder;
				filestring << directory.path().stem().string();
				retval = filestring.str();
			}
		}
		ImGui::End();
	}
	return retval;
}

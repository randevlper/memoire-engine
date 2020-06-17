#include "WorldEditor.h"
#include "dear-imgui/imgui.h"

namespace lb {
	namespace imgui {
		static bool windowOpen = false;

		void showWorldEditor()
		{
			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("Tools"))
				{
					if (ImGui::MenuItem("Open World Editor")) { windowOpen = true; }
					ImGui::EndMenu();
				}

				ImGui::EndMainMenuBar();
			}
		}
	}
}
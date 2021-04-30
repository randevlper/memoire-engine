#include "DebugEditor.h"
#include <dear-imgui/imgui.h>

#include "Engine/Core/WorldManager.h"
#include "Engine/Physics2D/Physics2D.h"

void me::imgui::debug::showDebugEditor()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("DEBUG"))
		{
			
			bool doSimulateWorld = WorldManager::getDoSimulate();
			if (ImGui::MenuItem("Simulate World", nullptr, &doSimulateWorld)) {
				WorldManager::setDoSimulate(doSimulateWorld);
			}

			bool doSimulatePhysics = Physics2D::getDoSimulate();
			if (ImGui::MenuItem("Simulate Physics", nullptr, &doSimulatePhysics)) {
				Physics2D::setDoSimulate(doSimulatePhysics);
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

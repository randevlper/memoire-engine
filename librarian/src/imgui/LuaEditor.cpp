#include "LuaEditor.h"

#include <dear-imgui/imgui.h>
#include "Engine/Core/LuaManager.h"

#include "Engine/Core/World.h"
#include "Engine/Core/WorldManager.h"


void reload() {
	LuaManager::destroy();
	LuaManager::init();
	me::WorldManager::loadWorld("assets/worlds/" + me::WorldManager::getWorld()->name);
}

void me::imgui::ShowLuaEditor()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("RELOAD"))
		{
			if (ImGui::MenuItem("World")) { reload(); }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

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

void open() {
	std::string text = "code assets\\worlds\\" + me::WorldManager::getWorld()->name + ".lua";
	system(text.c_str());
}

void openWindow() {
	std::string text = "explorer assets\\";
	system(text.c_str());
}

void me::imgui::ShowLuaEditor()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("LUA"))
		{
			if (ImGui::MenuItem("Open in Windows")) { openWindow(); }
			if (ImGui::MenuItem("Reload Lua")) { reload(); }
			if (ImGui::MenuItem("Open Lua")) { open(); }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

#include "WorldEditor.h"

#include <vector>

#include <dear-imgui/imgui.h>
#include <Engine/thirdparty/imgui/imgui_stdlib.h>

#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

namespace lb {
	namespace imgui {
		static bool windowOpen = false;
		static unsigned int selected = 0;

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

			if (!windowOpen) { return; }

			ImGui::Begin("World Editor", &windowOpen);
			ImGui::Text("World");

			World* world = me::WorldManager::getWorld();

			if (ImGui::Button("+", { 25,25 })) {
				world->create<Node2D>();
			}
			
			const std::vector<Node*> nodes = world->getNodes();

			ImGui::BeginChild("Node View", { 200, 0 }, true);
			for (size_t i = 0; i < nodes.size(); i++){
				if (ImGui::Selectable(nodes[i]->getName().c_str(), selected == i)) {
					selected = i;
				}
			}
			ImGui::EndChild();

			ImGui::SameLine();
			ImGui::BeginGroup();

			
			if (nodes.size() > 0) {
				Node* nodeSelected = nodes[selected];
				std::string nodeName = nodeSelected->getName();
				ImGui::InputText("node_name", &nodeName, ImGuiInputTextFlags_CharsNoBlank);
				//ImGui::InputInt("node_x",)

				nodeSelected->setName(nodeName);
			}

			ImGui::EndGroup();



			ImGui::End();
		}
	}
}
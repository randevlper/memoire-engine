#include "WorldEditor.h"

#include <vector>

#include <dear-imgui/imgui.h>
#include <Engine/thirdparty/imgui/imgui_stdlib.h>

#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

#include "Engine/UI/NodeUI.h"
#include "Engine/UI/Button.h"
#include "Engine/UI/Text.h"

#include <glm/gtc/type_ptr.hpp>

#include "Engine/Utilities/Debug.h"


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

				if (nodeSelected->getType() == "Node2D") {
					Node2D* node2DSelected = dynamic_cast<Node2D*>(nodeSelected);
					
					//Would be more performant to have the editor access the memory directly but this way its using the same interface as the User
					glm::vec2 pos = node2DSelected->transform.getLocalPosition();
					glm::vec2 scale = node2DSelected->transform.getLocalScale();
					float angle = node2DSelected->transform.getLocalAngle();

					ImGui::PushItemWidth(150);
					ImGui::InputFloat("Pos X", &pos.x);
					ImGui::SameLine();
					ImGui::InputFloat("Pos Y", &pos.y);
					ImGui::InputFloat("Scale X", &scale.x);
					ImGui::SameLine();
					ImGui::InputFloat("Scale Y", &scale.y);
					ImGui::InputFloat("Angle", &angle);

					node2DSelected->transform.setLocalPosition(pos);
					node2DSelected->transform.setLocalScale(scale);
					node2DSelected->transform.setLocalAngle(angle);
				}

				if (nodeSelected->getType() == "NodeUI" || 
					nodeSelected->getType() == "Button") {
					NodeUI* nodeUISelected = dynamic_cast<NodeUI*>(nodeSelected);

					glm::vec2 pos = nodeUISelected->rectTransform.getPosition();
					glm::vec2 size = nodeUISelected->rectTransform.getSize();

					ImGui::PushItemWidth(150);
					ImGui::InputFloat("Pos X", &pos.x);
					ImGui::SameLine();
					ImGui::InputFloat("Pos Y", &pos.y);
					ImGui::InputFloat("Size X", &size.x);
					ImGui::SameLine();
					ImGui::InputFloat("Size Y", &size.y);

					nodeUISelected->rectTransform.setPosition(pos);
					nodeUISelected->rectTransform.setSize(size);

					if (nodeSelected->getType() == "Button") {
						me::ui::Button* buttonSelected = dynamic_cast<me::ui::Button*>(nodeSelected);

						ImGui::ColorPicker4("ColorNormal", glm::value_ptr(buttonSelected->colorNormal));
						ImGui::SameLine();
						ImGui::ColorPicker4("ColorHighlight", glm::value_ptr(buttonSelected->colorClicked));
						ImGui::SameLine();
						ImGui::ColorPicker4("ColorClicked", glm::value_ptr(buttonSelected->colorHightlight));
						ImGui::SameLine();
						ImGui::ColorPicker4("ColorDisabled", glm::value_ptr(buttonSelected->colorDisabled));
						buttonSelected->setSize(size);
					}


				}


				nodeSelected->setName(nodeName);
			}

			ImGui::EndGroup();



			ImGui::End();
		}
	}
}
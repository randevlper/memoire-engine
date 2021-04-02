#include "WorldEditor.h"

#include <vector>
#include <string>
#include <filesystem>
#include <sstream>

#include <dear-imgui/imgui.h>
#include <Engine/thirdparty/imgui/imgui_stdlib.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "SDL_keycode.h"
#include "Engine/Core/Input.h"

#include "Engine/Core/FileUtility.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

#include "Engine/UI/NodeUI.h"
#include "Engine/UI/Button.h"
#include "Engine/UI/Text.h"

#include <glm/gtc/type_ptr.hpp>

#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/ObjectFactory.h"
#include "Engine/Core/Renderer.h"

#include "Engine/Nodes/Camera.h"
#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Sprite.h"

#include "Engine/IMGUI/ImguiUtilities.h"
#include "Engine/Utilities/TypeConversion.h"

namespace lb {
	namespace imgui {
		namespace worldEditor {
			static bool windowOpen = false;
			static int selected = 0;

			static const char* current_node_selected = "Node2D";
			const char* nodeTypes[] = { "Node2D", "NodeUI", "Button", "Camera", "Text", "SpriteRenderer" };
			const size_t nodeTypesCount = 6;

			static bool isWorldLoadSelectOpen = false;
			static std::filesystem::directory_entry worldLoadSelection = std::filesystem::directory_entry();

			static bool isSpriteLoadSelectOpen = false;
			static std::filesystem::directory_entry spriteLoadSelection = std::filesystem::directory_entry();

			const std::string worldsPath = "assets/worlds/";

			void showEditor()
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

				std::string file = lb::imgui::utilities::selectFile(isWorldLoadSelectOpen, worldLoadSelection, worldsPath, WORLD_FILE_TYPE);
				if (file != "null") {
					me::WorldManager::loadWorld(file);
					isWorldLoadSelectOpen = false;
				}

				ImGui::Begin("World Editor", &windowOpen, ImGuiWindowFlags_MenuBar);
				if (ImGui::BeginMenuBar()) {
					if (ImGui::BeginMenu("File###worldEditorFileMenu"))
					{
						if (ImGui::MenuItem("New..", "Ctrl+N")) { me::WorldManager::loadWorld(); }
						if (ImGui::MenuItem("Open..", "Ctrl+O")) { isWorldLoadSelectOpen = true; }
						if (ImGui::MenuItem("Save", "Ctrl+S")) {
							std::ostringstream fileStringName;
							fileStringName << me::WorldManager::getWorld()->name;
							fileStringName << ".world";
							FileUtility::writeStringFile(worldsPath.c_str(), fileStringName.str().c_str(),
								me::WorldManager::getWorld()->to_json().dump(4));
						}
						if (ImGui::MenuItem("Close", "Ctrl+W")) { windowOpen = false; }
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}
				

				
				World* world = me::WorldManager::getWorld();
				ImGui::InputText("World Name###WorldName", &world->name);
				ImGui::PushItemWidth(150);

				if (ImGui::BeginCombo("###node_selection", current_node_selected)) {

					for (size_t i = 0; i < nodeTypesCount; i++)
					{
						bool is_selected = (current_node_selected == nodeTypes[i]);
						if (ImGui::Selectable(nodeTypes[i], is_selected)) {
							current_node_selected = nodeTypes[i];
						}
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}

					}
					ImGui::EndCombo();
				}

				ImGui::SameLine();
				if (ImGui::Button("+", { 25,25 })) {
					Node* newNode = world->create(current_node_selected);

					if (strcmp("Camera", current_node_selected) == 0) {
						Camera* camera = dynamic_cast<Camera*>(newNode);
						if (Renderer::getCamera() == nullptr) {
							Renderer::setCamera(camera);
						}
					}
				}
				
				std::vector<Node*> nodes = world->getNodes();


				if (ImGui::Button("/\\", ImVec2(25, 25))) {
					lb::imgui::utilities::MoveItemUp<Node*>(nodes, selected);
				}

				ImGui::SameLine();
				if (ImGui::Button("\\/", ImVec2(25, 25))) {
					lb::imgui::utilities::MoveItemDown<Node*>(nodes, selected);
				}



				if (selected >= nodes.size()) {
					selected = 0;
				}

				if (ImGui::Button("-", { 25,25 })) {
					if (nodes.size() > 0) {
						world->destroy(nodes[selected]);
						selected--;
						if (selected < 0) {
							selected = 0;
						}
						nodes = world->getNodes();
					}
				}


				ImGui::BeginChild("Node View", { 200, 0 }, true);
				for (size_t i = 0; i < nodes.size(); i++) {
					if (ImGui::Selectable(nodes[i]->getName().c_str(), selected == i)) {
						selected = i;
					}
				}
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginGroup();

				glm::vec2 mousePos = {0,0};
				if (!ImGui::IsWindowFocused() && Input::getKey(SDL_SCANCODE_LCTRL)) {
					mousePos = Input::getMousePos();
					mousePos = me::util::convertInputToScreen(mousePos);
					mousePos = me::util::convertScreenToWorld(mousePos);
				}

				if (nodes.size() > 0) {
					Node* nodeSelected = nodes[selected];
					std::string nodeName = nodeSelected->getName();
					ImGui::InputText("node_name", &nodeName, ImGuiInputTextFlags_CharsNoBlank);
					//ImGui::InputInt("node_x",)
					ImGui::Text(nodeSelected->getType().c_str());


					if (nodeSelected->getType() == "Node2D" || 
						nodeSelected->getType() == "Camera" ||
						nodeSelected->getType() == "SpriteRenderer") {
						Node2D* node2DSelected = dynamic_cast<Node2D*>(nodeSelected);

						//Would be more performant to have the editor access the memory directly but this way its using the same interface as the User
						glm::vec2 pos = node2DSelected->transform.getLocalPosition();
						glm::vec2 scale = node2DSelected->transform.getLocalScale();
						float angle = node2DSelected->transform.getLocalAngle();

						if (mousePos != glm::vec2(0, 0)) {
							pos = mousePos;
						}

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

						if (nodeSelected->getType() == "SpriteRenderer") {
							SpriteRenderer* nodeSpriteRenderer = dynamic_cast<SpriteRenderer*>(nodeSelected);

							std::string spritepath = "";
							//Need nullptr check
							if (nodeSpriteRenderer->getSprite() == nullptr) {
								nodeSpriteRenderer->setSprite(AssetManager::get<Sprite>("assets/ui/box.png"));
							}
							spritepath = nodeSpriteRenderer->getSprite()->path;

							ImGui::Text(spritepath.c_str());

							if (ImGui::Button("Load###SpriteLoadButton")) {
								isSpriteLoadSelectOpen = true;
							}

							std::string newSprite = lb::imgui::utilities::selectFile(isSpriteLoadSelectOpen, spriteLoadSelection, "assets/sprites/", ".png");
							if (newSprite != "null") {
								newSprite += ".png";
								if (newSprite != spritepath) {
									//This should be turned into a function
									Sprite* sprite = AssetManager::get<Sprite>(newSprite);
									if (sprite == nullptr) {
										AssetManager::load(newSprite, "");
										sprite = AssetManager::get<Sprite>(newSprite);
										nodeSpriteRenderer->setSprite(sprite);
										isSpriteLoadSelectOpen = false;
									}
									else {
										sprite = AssetManager::get<Sprite>(newSprite);
										nodeSpriteRenderer->setSprite(sprite);
										isSpriteLoadSelectOpen = false;
									}
									//-----
								}
							}
							
						}
					}

					if (nodeSelected->getType() == "NodeUI" ||
						nodeSelected->getType() == "Button" || 
						nodeSelected->getType() == "Text") {

						static glm::vec2 lastSize;
						static glm::vec2 lastPos;
						NodeUI* nodeUISelected = dynamic_cast<NodeUI*>(nodeSelected);

						glm::vec2 pos = nodeUISelected->rectTransform.getPosition();
						glm::vec2 size = nodeUISelected->rectTransform.getSize();

						if (mousePos != glm::vec2(0,0)) {
							pos = mousePos;
						}

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

							ImGui::InputText("LuaOnClick", &buttonSelected->luaOnClick);

							ImGui::ColorPicker4("ColorNormal", glm::value_ptr(buttonSelected->colorNormal));
							ImGui::SameLine();
							ImGui::ColorPicker4("ColorHighlight", glm::value_ptr(buttonSelected->colorHightlight));
							ImGui::SameLine();
							ImGui::ColorPicker4("ColorClicked", glm::value_ptr(buttonSelected->colorClicked));
							ImGui::SameLine();
							ImGui::ColorPicker4("ColorDisabled", glm::value_ptr(buttonSelected->colorDisabled));

							//Sprite

							if (lastSize != size || lastPos != pos) {
								buttonSelected->setSize(size);
							}
						}

						if (nodeSelected->getType() == "Text") {
							me::ui::Text* textSelected = dynamic_cast<me::ui::Text*>(nodeSelected);
							static std::string lastText;

							std::string text = textSelected->getText();
							glm::vec4 color = textSelected->getColor();

							//Text
							ImGui::InputTextMultiline("TextText", &text, { 300,200 });
							//Font

							//Color
							ImGui::ColorPicker4("ColorNormal", glm::value_ptr(color));

							if (lastText != text || lastSize != size || lastPos != pos) {
								textSelected->setText(text);
							}
							textSelected->setColor(color);
							lastText = text;
						}

						lastSize = size;
						lastPos = pos;


					}

					nodeSelected->setName(nodeName);
				}

				ImGui::EndGroup();

				world->setNodes(nodes);

				ImGui::End();
			}
		}
	}
}
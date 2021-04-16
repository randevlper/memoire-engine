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
#include "Engine/Physics2D/Body2D.h"

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Sprite.h"

#include "Engine/IMGUI/ImguiUtilities.h"
#include "Engine/Utilities/TypeConversion.h"

#include "Engine/Physics2D/Physics2D.h"

namespace me {
	namespace imgui {
		namespace worldEditor {
			static bool isInit = false;
			static bool windowOpen = false;
			static int selected = 0;

			static const char* current_node_selected = "Node2D";
			std::vector<std::string> nodeTypes = { "NodeUI", "Button", "Text"};

			static bool isWorldLoadSelectOpen = false;
			static std::filesystem::directory_entry worldLoadSelection = std::filesystem::directory_entry();

			static bool isSpriteLoadSelectOpen = false;
			static std::filesystem::directory_entry spriteLoadSelection = std::filesystem::directory_entry();

			const std::string worldsPath = "assets/worlds/";

			//Map?
			static std::unordered_map<std::string, std::function<void(Node*)>> _nodeEditors = std::unordered_map<std::string, std::function<void(Node*)>>();

			void showEditor()
			{
				if (!isInit) {
					addNodeEditor("Node2D", editorNode2D);
					addNodeEditor("SpriteRenderer", editorSpriteRenderer);
					addNodeEditor("Camera", editorCamera);
					addNodeEditor("Body2D", editorBody2D);
					isInit = true;
				}

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

					for (size_t i = 0; i < nodeTypes.size(); i++)
					{
						bool is_selected = (current_node_selected == nodeTypes[i]);
						if (ImGui::Selectable(nodeTypes[i].c_str(), is_selected)) {
							current_node_selected = nodeTypes[i].c_str();
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
					std::string nodeName = nodes[i]->getName() + "###nodev" + std::to_string(i);
					if (ImGui::Selectable(nodeName.c_str(), selected == i)) {
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
					bool nodeIsEnabled = nodeSelected->getIsEnabled();
					ImGui::InputText("node_name", &nodeName, ImGuiInputTextFlags_CharsNoBlank);
					ImGui::Checkbox("node_is_enabled", &nodeIsEnabled);
					std::string nodeType = nodeSelected->getType();
					ImGui::Text(nodeType.c_str());

					nodeSelected->setIsEnabled(nodeIsEnabled);
					nodeSelected->setName(nodeName);

					if (nodeType == "NodeUI" ||
						nodeType == "Button" ||
						nodeType == "Text") {

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



						if (nodeType == "Button") {
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

						if (nodeType == "Text") {
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

					std::unordered_map<std::string, std::function<void(Node*)>>::iterator it = _nodeEditors.find(nodeType);
					if (it != _nodeEditors.end())
					{
						it->second(nodeSelected);
					}

				}

				ImGui::EndGroup();

				world->setNodes(nodes);

				ImGui::End();
			}

			void addNodeEditor(std::string nodeName, std::function<void(Node*)> node)
			{
				for (size_t i = 0; i < nodeTypes.size(); i++)
				{
					if (nodeTypes[i] == nodeName) {
						Debug::LogError("[Worldeditor] " + nodeName + " already is added to the editor.");
						return;
					}
				}

				nodeTypes.push_back(nodeName);
				_nodeEditors.insert(std::pair<std::string, std::function<void(Node*)>>(nodeName, node));
			}

			void editorNode2D(Node* node)
			{
				Node2D* node2DSelected = dynamic_cast<Node2D*>(node);

				Transform transform = node2DSelected->getTransform();
				
				std::string parent = "Parent: ";
				if (transform.getParent() != nullptr) {
					parent +=  transform.getParent()->getName();
				}
				else {
					parent += "null";
				}
				ImGui::Text(parent.c_str());

				std::string child = "Child: ";
				if (transform.getChild() != nullptr) {
					child += transform.getChild()->getName();
				}
				else {
					child += "null";
				}
				ImGui::Text(child.c_str());


				//Would be more performant to have the editor access the memory directly but this way its using the same interface as the User
				glm::vec2 pos = transform.getLocalPosition();
				glm::vec2 scale = transform.getLocalScale();
				float angle = transform.getLocalAngle();

				ImGui::PushItemWidth(150);
				ImGui::InputFloat("Pos X", &pos.x);
				ImGui::SameLine();
				ImGui::InputFloat("Pos Y", &pos.y);
				ImGui::InputFloat("Scale X", &scale.x);
				ImGui::SameLine();
				ImGui::InputFloat("Scale Y", &scale.y);
				ImGui::InputFloat("Angle", &angle);


				transform.setLocalPosition(pos);
				transform.setLocalScale(scale);
				transform.setLocalAngle(angle);

				node2DSelected->setTransform(transform);
			}

			void editorSpriteRenderer(Node* node)
			{
				editorNode2D(node);

				SpriteRenderer* nodeSpriteRenderer = dynamic_cast<SpriteRenderer*>(node);

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

			void editorCamera(Node* node)
			{
				editorNode2D(node);
			}

			void editorBody2D(Node* node)
			{
				Body2D* body2Dselected = dynamic_cast<Body2D*>(node);
				glm::vec2 pos = body2Dselected->getPosition();
				bool isAwake = body2Dselected->isAwake();
				bool isEnabled = body2Dselected->isEnabled();

				static glm::vec2 bodyLastPos;

				ImGui::PushItemWidth(150);
				ImGui::InputFloat("Pos X", &pos.x);
				ImGui::SameLine();
				ImGui::InputFloat("Pos Y", &pos.y);
				ImGui::Checkbox("IsAwake", &isAwake);
				ImGui::Checkbox("IsEnabled", &isEnabled);

				static int bodyWidth = 10;
				static int bodyHeight = 10;
				ImGui::InputInt("Width###Body2DWidth", &bodyWidth);
				ImGui::InputInt("Height###Body2DHeight", &bodyHeight);
				if (bodyWidth < 10) { bodyWidth = 10; }
				if (bodyHeight < 10) { bodyHeight = 10; }

				if (ImGui::Button("Build###bodyBuild")) {
					body2Dselected->setupBox(pos.x, pos.y, bodyWidth, bodyHeight,
						body2Dselected->getBodyType(), body2Dselected->getCatagory(),
						body2Dselected->getMask(), body2Dselected->isSensor());
				}

				body2Dselected->setIsAwake(isAwake);
				if (bodyLastPos != pos) {
					bodyLastPos = pos;
					body2Dselected->setPosition(bodyLastPos);
				}
			}

		}
	}
}
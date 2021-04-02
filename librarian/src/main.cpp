#include "Engine/Core/Context.h"
#include "Engine/Core/Renderer.h"

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"
#include "Engine/Core/Input.h"

#include "Engine/UI/Button.h"

#include "assetmanagement/DialogueLoader.h"
#include "nodes/DialogueWriter.h"

#include "Engine/Tools/imgui_bgfx.h"
#include "imgui/DialogueEditor.h"
#include "imgui/WorldEditor.h"
#include "imgui/LuaEditor.h"

#include "core/luabindings.h"

int main(int argc, char** argv) {
	{
		unsigned int renderWidth = 1280;
		unsigned int rednerHeight = 720;
		unsigned int windowWidth = 1280;
		unsigned int windowHeight = 720;

		lb::InitLuaBindings();
		ContextWindowParems cWinParems = { "Seaside", renderWidth, rednerHeight, windowWidth, windowHeight, 60 , argc, argv };
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}
		AssetManager::initLoader<lb::DialogueLoader>();
		me::WorldManager::loadWorld("assets/worlds/mainmenu");

		lb::DialogueWriter::init();
		while (!Context::getShouldClose())
		{
			Context::tick();

			me::WorldManager::tick();

			//Debug code to test world editor
			World* world = me::WorldManager::getWorld();
			if (world != nullptr) {
				const std::vector<Node*> nodes = world->getNodes();
				for (size_t i = 0; i < nodes.size(); i++)
				{
					if (nodes[i]->getType() == "Node2D") {
						Node2D* node2DSelected = dynamic_cast<Node2D*>(nodes[i]);
						Debug::DrawTransform(&node2DSelected->transform);
					}
					if (nodes[i]->getType() == "Button") {
						me::ui::Button* buttonSelected = dynamic_cast<me::ui::Button*>(nodes[i]);
						if (!me::imgui::isIMGUIOpen()) {
							buttonSelected->sendMouseInfo(Input::getMousePos(), Input::getMouseKeyDown(1));
						}
					}
				}
			}

			me::WorldManager::render();

			if (me::imgui::isIMGUIOpen()) {
				me::imgui::beginFrame();
				lb::imgui::dialogueEditor::showEditor();
				lb::imgui::worldEditor::showEditor();
				me::imgui::ShowLuaEditor();
				me::imgui::endFrame();
			}

			Renderer::render();
			
			//Load new World here.
			me::WorldManager::postLogic();
		}

		Context::quit();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}
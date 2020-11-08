#include <iostream>
#include <list>
#include <functional>
#include <string>
#include <fstream>

#include <bgfx/bgfx.h>
#include <glm/vec2.hpp>
#include <SDL_pixels.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Engine/Core/Context.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/World.h"

#include "Engine/Core/WorldManager.h"
#include "Engine/Core/Audio.h"
#include "Engine/Core/LuaManager.h"
#include "Engine/Core/Input.h"

#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/AssetManagement/Font.h"
#include "Engine/AssetManagement/AudioClip.h"

#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/Nodes/TextRenderer.h"
#include "Engine/Nodes/Camera.h"
#include "Engine/Nodes/AudioSource.h"

#include "Engine/AssetManagement/JSON.h"

#include "Engine/UI/Button.h"
#include "Engine/UI/Text.h"

#include "Engine/Tools/imgui_bgfx.h"

#include "assetmanagement/DialogueLoader.h"
#include "nodes/DialogueWriter.h"
#include "imgui/DialogueEditor.h"
#include "imgui/WorldEditor.h"


//AudioSource* audioSource;
//me::ui::Text* textTest;
//
//void ohno() {
//	audioSource->play();
//	textTest->setText("Ays: He was asking for it!\nAne: That was not helpful.\nHe wanted a good time!\nAne: Your idea of a good time is very diffrent from the norm.");
//}

int main(int argc, char** argv) {
	{
		json config;
		{
			std::ifstream configFile("config.json");
			configFile >> config;
			configFile.close();
		}
		//j["resolution"] = { 1920, 1080 };
		//config file load

		//FileUtility::writeStringFile("config.json", j.dump());

		unsigned int width = 1280;
		unsigned int height = 720;

		width = config["resolution"][0];
		height = config["resolution"][1];

		//Should handle errors with some helper functions
		//std::string err;
		//err.append(j["resolution"][0].type_name());
		//if (err == "number") {
		//	width = j["resolution"][0];
		//}
		//else {
		//	err.append(" is not right type!");
		//	Debug::Log(err);
		//}

		ContextWindowParems cWinParems = { "Seaside", width, height, 60 , argc, argv };
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}
		AssetManager::initLoader<lb::DialogueLoader>();

		/*audioSource = world->create<AudioSource>();
		audioSource->setAudioClip(audioTest);
		*/

		//Callbacks for changing rect properties?

		//UI button - Sprites
		//UI Panels - Take code from button and implemnt sprites
		//UI Textbox - text formatting hell
		//Audio looping

		me::WorldManager::loadWorld("assets/worlds/mainmenu");

		while (!Context::getShouldClose())
		{
			Context::tick();

			if(Input::getKeyDown(SDL_SCANCODE_SPACE) && !me::imgui::isAnyWindowFocused()) {
				//Progress Text	
				//dialogueWriter->progress();
			}

			me::WorldManager::tick();

			//Debug code to test world editor
			World* world = me::WorldManager::getWorld();
			const std::vector<Node*> nodes = world->getNodes();
			for (size_t i = 0; i < nodes.size(); i++)
			{
				if (nodes[i]->getType() == "Node2D") {
					Node2D* node2DSelected = dynamic_cast<Node2D*>(nodes[i]);
					Debug::DrawTransform(&node2DSelected->transform);
				}
				if (nodes[i]->getType() == "Button") {
					me::ui::Button* buttonSelected = dynamic_cast<me::ui::Button*>(nodes[i]);
					buttonSelected->sendMouseInfo(Input::getMousePos(), Input::getMouseKeyDown(1));
					
				}

			}

			me::WorldManager::render();

			me::imgui::beginFrame();
			lb::imgui::dialogueEditor::showEditor(nullptr);
			lb::imgui::worldEditor::showEditor();
			me::imgui::endFrame();

			Renderer::render();
			
		}

		lb::imgui::dialogueEditor::destroy();
		Context::quit();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}
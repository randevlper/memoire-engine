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
#include "Engine/Utilities/DebugMemory.h"

//#include "Engine/Tools/aseprite.h"
#include "Engine/Core/Input.h"
#include "Engine/Data/Transform.h"
#include "Engine/Utilities/Debug.h"

#include "Engine/AssetManagement/AssetManager.h"
//Assets should have their own Asset folder for organization
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/AssetManagement/Font.h"
#include "Engine/AssetManagement/AudioClip.h"
#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/Nodes/TextRenderer.h"
#include "Engine/Nodes/Camera.h"
#include "Engine/Core/Audio.h"
#include "Engine/Core/LuaManager.h"
#include "Engine/Nodes/AudioSource.h"

#include "Engine/AssetManagement/JSON.h"

#include "Engine/UI/Button.h"
#include "Engine/UI/Text.h"

#include "Engine/Tools/imgui_bgfx.h"

#include "Engine/Core/WorldManager.h"


#include "nodes/DialogueWriter.h"
#include "imgui/DialogueEditor.h"
#include "imgui/WorldEditor.h"
#include "assetmanagement/DialogueLoader.h"

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
		me::imgui::create();

		AssetManager::init();
		AssetManager::initLoader<lb::DialogueLoader>();

		/*audioSource = world->create<AudioSource>();
		audioSource->setAudioClip(audioTest);


		me::ui::Button* buttonTest = world->create<me::ui::Button>();
		buttonTest->onClick = ohno;
		buttonTest->rectTransform.setPosition({ Context::getWindowWidth() * 0.8f, Context::getWindowHeight() * 0.25f - 50 });
		buttonTest->setSize({ Context::getWindowWidth() * 0.2f, 50 });
		buttonTest->setSprite(AssetManager::get<Sprite>("assets/ui/box.png"));
		*/

		//Callbacks for changing rect properties?

		//UI button - Sprites
		//UI Panels - Take code from button and implemnt sprites
		//UI Textbox - text formatting hell
		//Audio looping


		/*
		Dialouge
		cppJSON

		IMGUI Dialouge Editor

		Want a UI editor but no need for the two scenes
		*/
		me::WorldManager::loadWorld();

		LuaManager::init();
		//LuaManager::test();

		while (!Context::getShouldClose())
		{
			Context::tick();

			if(Input::getKeyDown(SDL_SCANCODE_SPACE) && !me::imgui::isAnyWindowFocused()) {
				//Progress Text	
				//dialogueWriter->progress();
			}

			me::WorldManager::tick();

			//bgfx::dbgTextPrintf(0, 3, 0x0f, "Camera X: %f Camera Y: %f", cam->transform.getPosition().x, cam->transform.getPosition().y);
			//bgfx::dbgTextPrintf(0, 4, 0x0f, "Mouse X: %f Mouse Y: %f", Input::getMouseWheel().x, Input::getMouseWheel().y);


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
		LuaManager::destroy();

		lb::imgui::dialogueEditor::destroy();
		me::WorldManager::unLoadWorld();
		TextRenderer::destroy();
		SpriteRenderer::destroy();
		FileUtility::destroy();
		AssetManager::destroy();
		me::imgui::destroy();
		Context::quit();
	}
	

	_CrtDumpMemoryLeaks();
	return 0;
}
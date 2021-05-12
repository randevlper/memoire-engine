#include "Engine/Core/Context.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"

#include "Engine/Physics2D/Physics2D.h"
#include "Engine/Utilities/ObjectFactory.h"

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Sprite.h"

#include "Engine/IMGUI/imgui_bgfx.h"
#include "Engine/IMGUI/WorldEditor.h"
#include "Engine/IMGUI/LuaEditor.h"
#include "Engine/IMGUI/DebugEditor.h"

#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "Engine/Physics2D/Body2D.h"
#include "Engine/Nodes/SpriteRenderer.h"

#include "collision.h"
#include "fish.h"
#include "fishKiller.h"
#include "fishSpawner.h"
#include "fishSpawnerManager.h"
#include "hook.h"
#include "net.h"
#include "obstacle.h"

#include "playerController.h"
#include "worldEditor.h"

#include "SDL.h"

int main(int argc, char** argv) {
	{
		float iExistSoItCompiles = 0.0f; //http://forums.libsdl.org/viewtopic.php?p=47179

		unsigned int renderWidth = 1920;
		unsigned int rednerHeight = 1080;
		unsigned int windowWidth = 1920;
		unsigned int windowHeight = 1080;

		ContextWindowParems cWinParems = { "Fish", renderWidth, rednerHeight, windowWidth, windowHeight, 60 , argc, argv };
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}
		ADD_OBJECT_MAP(Fish)
		ADD_OBJECT_MAP(Obstacle)
		ADD_OBJECT_MAP(FishKiller)
		ADD_OBJECT_MAP(Hook)
		ADD_OBJECT_MAP(Net)
		ADD_OBJECT_MAP(FishSpawner)
		ADD_OBJECT_MAP(FishSpawnerManager)
		ADD_OBJECT_MAP(PlayerController)

		
		me::imgui::worldEditor::addNodeEditor("Fish", fish::editorFish);
		me::imgui::worldEditor::addNodeEditor("FishSpawner", fish::editorFishSpawner);
		me::imgui::worldEditor::addNodeEditor("FishSpawnerManager", fish::editorFishSpawnerManager);
		me::imgui::worldEditor::addNodeEditor("Net", fish::editorNet);
		me::imgui::worldEditor::addNodeEditor("PlayerController", fish::editorPlayerController);

		AssetManager::load("assets/sprites/fishtest.png", "");
		AssetManager::load("assets/sprites/fishtestb.png", "");
		AssetManager::load("assets/sprites/fishtestwhale.png", "");


		AssetManager::load("assets/sprites/debrie.png", "");
		//Diffrent types of fish
		// Points, Speed, layers 0 - 4, 
		AssetManager::load("assets/sprites/arrowbackground.png", "");
		AssetManager::load("assets/sprites/arrowup.png", "");
		AssetManager::load("assets/sprites/arrowdown.png", "");
		AssetManager::load("assets/sprites/arrowleft.png", "");
		AssetManager::load("assets/sprites/arrowright.png", "");

		me::WorldManager::loadWorld("assets/worlds/testworld");
		me::WorldManager::postRender();

		Physics2D::setGravity({ 0,0 });

		while (!Context::getShouldClose())
		{
			Context::tick();
			
			me::WorldManager::tick();
			Physics2D::tick();
			
			me::WorldManager::render();
			
			World* world = me::WorldManager::getWorld();
			std::vector<Node*> nodes = world->getNodes();
			for (size_t i = 0; i < nodes.size(); i++)
			{
				if (nodes[i]->getType() == "FishSpawner" || nodes[i]->getType() == "PlayerController") {
					Node2D* node2DSelected = dynamic_cast<Node2D*>(nodes[i]);
					Debug::DrawTransform(&node2DSelected->getTransform());
				}
			}

			Renderer::render();
			
			me::WorldManager::postRender();

			if (me::imgui::isIMGUIOpen()) {
				me::imgui::beginFrame();
				me::imgui::debug::showDebugEditor();
				me::imgui::worldEditor::showEditor();
				me::imgui::ShowLuaEditor();
				me::imgui::endFrame();
			}
		}
		Context::quit();
	}
	_CrtDumpMemoryLeaks();
}
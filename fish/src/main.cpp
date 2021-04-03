#include "Engine/Core/Context.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/Physics2D.h"

#include "Engine/IMGUI/imgui_bgfx.h"
#include "Engine/IMGUI/WorldEditor.h"
#include "Engine/IMGUI/LuaEditor.h"

#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "Engine/Nodes/Body2D.h"

#include "fish.h"
#include "hook.h"

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
		me::WorldManager::loadWorld();
		me::WorldManager::postLogic();

		{
			World* gWorld = me::WorldManager::getWorld();
			if (gWorld != nullptr) {
				Body2D *floor = gWorld->create<Body2D>();
				floor->setupBox(0, -100, 500, 50, Body2DType::Static);

				Body2D* b1 = gWorld->create<Body2D>();
				b1->setupBox(0, 300, 10, 10, Body2DType::Dynamic);

				Fish* fish = gWorld->create<Fish>();
				fish->setupBox(0, 400, 10, 10, Body2DType::Dynamic);

				Fish* fish2 = gWorld->create<Fish>();
				fish2->setupBox(0, 450, 10, 10, Body2DType::Dynamic);

				Hook* hook = gWorld->create<Hook>();
				hook->setupBox(0, 100, 100, 50, Body2DType::Static, true);
			}
		}
		
		
		while (!Context::getShouldClose())
		{
			Context::tick();
			me::WorldManager::tick();
			Physics2D::tick();
			me::WorldManager::render();
			Renderer::render();

			
			
			me::WorldManager::postLogic();

			if (me::imgui::isIMGUIOpen()) {
				me::imgui::beginFrame();
				me::imgui::worldEditor::showEditor();
				me::imgui::ShowLuaEditor();
				me::imgui::endFrame();
			}
		}
		Context::quit();
	}
	_CrtDumpMemoryLeaks();
}
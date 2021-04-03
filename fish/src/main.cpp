#include "Engine/Core/Context.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"
#include "Engine/Core/Input.h"
#include "Engine/IMGUI/imgui_bgfx.h"
#include "Engine/Core/Physics2D.h"

#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "Engine/Nodes/Body2D.h"

int main(int argc, char** argv) {
	{
		float iExistSoItCompiles = 0.0f; //http://forums.libsdl.org/viewtopic.php?p=47179

		unsigned int renderWidth = 1280;
		unsigned int rednerHeight = 720;
		unsigned int windowWidth = 1280;
		unsigned int windowHeight = 720;

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
				floor->setupBox(0.0f, -1.0f, 5.0f, 0.5f, Body2DType::Static);

				Body2D* block = gWorld->create<Body2D>();
				block->setupBox(0.0f, 4.0f, 0.5f, 0.5f, Body2DType::Dynamic);
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
				me::imgui::endFrame();
			}
		}
		Context::quit();
	}
	_CrtDumpMemoryLeaks();
}
#include "Engine/Core/Context.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"
#include "Engine/Tools/imgui_bgfx.h"

#include "Engine/Utilities/Debug.h"

int main(int argc, char** argv) {
	{
		float iExistSoItCompiles = 0.0f;

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
		while (!Context::getShouldClose())
		{
			Context::tick();
			me::WorldManager::tick();
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
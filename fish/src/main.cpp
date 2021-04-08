#include "Engine/Core/Context.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/Physics2D.h"
#include "Engine/Utilities/ObjectFactory.h"

#include "Engine/AssetManagement/AssetManager.h"
#include "Engine/AssetManagement/Sprite.h"

#include "Engine/IMGUI/imgui_bgfx.h"
#include "Engine/IMGUI/WorldEditor.h"
#include "Engine/IMGUI/LuaEditor.h"

#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include <SDL_keycode.h>

#include "Engine/Nodes/Body2D.h"
#include "Engine/Nodes/SpriteRenderer.h"

#include "collision.h"
#include "fish.h"
#include "fishKiller.h"
#include "fishSpawner.h"
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
		ADD_OBJECT_MAP(Fish);
		ADD_OBJECT_MAP(FishKiller);
		ADD_OBJECT_MAP(Hook);
		ADD_OBJECT_MAP(FishSpawner)

		me::WorldManager::loadWorld("assets/worlds/testworld");
		me::WorldManager::postRender();

		Physics2D::setGravity({ 0,0 });

		glm::vec2 dir = { 0,0 };
		float speed = 10;
		
		while (!Context::getShouldClose())
		{
			Context::tick();
			
			me::WorldManager::tick();

			//spawner->tick(Context::getDeltaTime());

			dir = { 0,0 };
			if (Input::getKey(SDL_SCANCODE_LEFT)) {
				dir.x += -1;
			}
			if (Input::getKey(SDL_SCANCODE_RIGHT)) {
				dir.x += 1;
			}
			if (Input::getKey(SDL_SCANCODE_UP)) {
				dir.y += 1;
			}
			if (Input::getKey(SDL_SCANCODE_DOWN)) {
				dir.y += -1;
			}
			//hook->setVelocity(dir * speed);
			
			Physics2D::tick();
			
			me::WorldManager::render();
			
			Renderer::render();

			
			
			me::WorldManager::postRender();

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
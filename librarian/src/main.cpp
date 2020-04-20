#include <iostream>
#include <list>

#include <bgfx/bgfx.h>
#include <glm/vec2.hpp>
#include <SDL_pixels.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>

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
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/AssetManagement/FontLoader.h"
#include "Engine/AssetManagement/Font.h"
#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/Nodes/TextRenderer.h"
#include "Engine/Nodes/Camera.h"

int main(int argc, char** argv) {
	{
		ContextWindowParems cWinParems = { "Project-Memoire", 1280, 720, 60 , argc, argv};
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}

		AssetManager::init();

		World* world = DBG_NEW World();

		Camera* cam = world->create <Camera>();
		cam->transform.setLocalPosition({ 0,0 });

		Renderer::setCamera(cam);
		
		Font* fontTest = AssetManager::get<Font>("assets/fonts/cmunrm.ttf");

		TextRenderer* textRenderer = world->create <TextRenderer>();
		textRenderer->setFont(fontTest);
		textRenderer->transform.setLocalPosition({ -Context::getWindowWidth() / 2,0 });
		textRenderer->transform.setLocalScale({ 0.5f,0.5f });
		textRenderer->setText("OHAYOUUUUUU!!!!!");

		while (!Context::getShouldClose())
		{
			Context::tick();
			glm::vec2 mousePos = Input::getMousePos();
			mousePos = cam->screenToWorld(mousePos);


			textRenderer->render();
			
			//Renderer::renderLine(mousePos, mousePos, glm::vec4(255,0,0,255), 10.0f);

			bgfx::dbgTextPrintf(0, 3, 0x0f, "Camera X: %f Camera Y: %f", cam->transform.getPosition().x, cam->transform.getPosition().y);
			bgfx::dbgTextPrintf(0, 4, 0x0f, "Mouse X: %f Mouse Y: %f", mousePos.x, mousePos.y);

			Renderer::render();
			
		}
		delete(world);
		TextRenderer::destroy();
		SpriteRenderer::destroy();
		FileUtility::destroy();
		AssetManager::destroy();
		Context::quit();
	}
	

	_CrtDumpMemoryLeaks();
	return 0;
}
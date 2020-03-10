/*
Memoir Engine
2D Game engine

Editor
	Imgui

Engine

Data Oriented
	Generate Data -> Modify -> Renderer
*/

#include "Engine/Utilities/DebugMemory.h"

#include <iostream>
#include <list>

#include <bgfx/bgfx.h>
#include <glm/vec2.hpp>
#include <SDL_pixels.h>
#include <SDL_keycode.h>


#include "Engine/Core/Context.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/Physics.h"
#include "Engine/Data/AseData.h"
//#include "Engine/Tools/aseprite.h"
#include "Engine/Core/Input.h"
#include "Engine/Data/Transform.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Nodes/Node.h"
//#include "Engine/Nodes/Collider.h"
#include "Engine/Nodes/Body.h"
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/Nodes/SpriteRenderer.h"

#include "Engine/AssetManagement/FontLoader.h"
#include "Engine/AssetManagement/Font.h"

#include "Engine/Nodes/TextRenderer.h"
#include "Engine/AssetManagement/AssetManager.h"

#include"Engine/Nodes/TilemapRenderer.h"
#include "Engine/AssetManagement/Tilemap.h"

struct GridNode
{
	unsigned int floorID; //ground
	unsigned int thingID; //nothing, wall
	unsigned int roofID; //none, ceiling
};

struct Grid
{
	unsigned int width, height;
	std::list<GridNode> nodes;
};


//ThingData
//Grid
//GridRenderer

int main(int argc, char** argv) {
	{
		ContextWindowParems cWinParems = { "Project-Memoire", 1280, 720, 640, 360, 60 , argc, argv};
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}
		Node test;
		test.transform.setLocalPosition(glm::vec2(20, 20));
		test.transform.setLocalScale(glm::vec2(10, 10));
		Node test2;
		test2.transform.setLocalPosition(glm::vec2(50, 50));
		test.transform.setParent(&test2);

		Body col({});

		Transform cameraPos;
		cameraPos.setLocalPosition({ 0,0 });

		AssetManager::init();

		AssetManager::load("assets/ayse.png","");
		AssetManager::load("assets/tiles/grass.png", "");

		AssetManager::load("assets/fonts/cmunrm.ttf", "64");

		Sprite* ayse = AssetManager::get<Sprite>("assets/ayse.png");
		Sprite* sprite = AssetManager::get<Sprite>("assets/tiles/grass.png");

		SpriteRenderer* spriteRenderer = DBG_NEW SpriteRenderer();
		spriteRenderer->setSprite(ayse);

		SpriteRenderer* spriteRenderer2 = DBG_NEW SpriteRenderer();
		spriteRenderer2->setSprite(sprite);
		spriteRenderer2->transform.depth = 2.0f;

		spriteRenderer2->transform.setLocalPosition({ -100,-100 });
		
		Font* fontTest = AssetManager::get<Font>("assets/fonts/cmunrm.ttf");

		TextRenderer* textRenderer = DBG_NEW TextRenderer();
		textRenderer->setFont(fontTest);
		textRenderer->transform.setLocalPosition({ -Context::getWindowWidth() / 2,0 });
		textRenderer->transform.setLocalScale({ 0.5f,0.5f });
		textRenderer->setText("OHAYOUUUUUU!!!!!");
		textRenderer->setText("YEEEEEEEhAw");

		TilemapRenderer* tilemapRen = DBG_NEW TilemapRenderer();
		Tilemap* tilemap = DBG_NEW Tilemap();
		tilemapRen->setTilemap(tilemap);
		tilemap->testSprite = sprite;

		Uint32 ticks = 0;
		while (!Context::getShouldClose())
		{
			ticks++;
			Context::tick();

			glm::vec2 movement = glm::vec2();
			if (Input::getKey(SDL_SCANCODE_D)) {
				movement.x = Context::getDeltaTime();
			}
			if (Input::getKey(SDL_SCANCODE_A)) {
				movement.x = -Context::getDeltaTime();
			}
			if (Input::getKey(SDL_SCANCODE_W)) {
				//Debug::Log("Up!");
				movement.y = Context::getDeltaTime();
			}
			if (Input::getKey(SDL_SCANCODE_S)) {
				//Debug::Log("Up!");
				movement.y = -Context::getDeltaTime();
			}

			float speed = 50.0f;
			cameraPos.translate((movement * speed));
			Physics::tick();

			spriteRenderer->transform.setLocalScale({ sin((ticks * Context::getDeltaTime()) /10), 1 });
			spriteRenderer2->render();
			spriteRenderer->render();
			textRenderer->render();
			tilemapRen->render();

			
			
			Renderer::setCameraPos(cameraPos.getPosition().x,cameraPos.getPosition().y);

			glm::ivec2 mousePos = Input::getMouseWorldPos();

			bgfx::dbgTextPrintf(0, 3, 0x0f, "Camera X: %f Camera Y: %f", cameraPos.getPosition().x, cameraPos.getPosition().y);
			bgfx::dbgTextPrintf(0, 4, 0x0f, "Mouse X: %i Mouse Y: %i", mousePos.x, mousePos.y);


			Renderer::render();
			
		}

		delete(tilemapRen);
		delete(tilemap);
		delete(textRenderer);
		delete(spriteRenderer);
		delete(spriteRenderer2);
		TextRenderer::destroy();
		SpriteRenderer::destroy();
		FileUtility::destroy();
		AssetManager::destroy();
		Context::quit();
	}
	

	_CrtDumpMemoryLeaks();
	return 0;
}
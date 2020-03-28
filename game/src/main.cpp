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

#include "Engine/Core/World.h"

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

#include "Engine/Nodes/Camera.h"

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
		ContextWindowParems cWinParems = { "Project-Memoire", 1280, 720, 60 , argc, argv};
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

		AssetManager::init();

		AssetManager::load("assets/ayse.png","");
		AssetManager::load("assets/tiles/grass.png", "");

		AssetManager::load("assets/fonts/cmunrm.ttf", "64");

		Sprite* ayse = AssetManager::get<Sprite>("assets/ayse.png");
		Sprite* sprite = AssetManager::get<Sprite>("assets/tiles/grass.png");

		World* world = DBG_NEW World();

		Camera* cam = world->create <Camera>();
		cam->transform.setLocalPosition({ 0,0 });

		Renderer::setCamera(cam);

		SpriteRenderer* spriteRenderer = world->create<SpriteRenderer>();
		spriteRenderer->setSprite(ayse);

		SpriteRenderer* spriteRenderer2 = world->create<SpriteRenderer>();
		spriteRenderer2->setSprite(sprite);
		spriteRenderer2->transform.depth = 2.0f;

		spriteRenderer2->transform.setLocalPosition({ -100,-100 });
		
		Font* fontTest = AssetManager::get<Font>("assets/fonts/cmunrm.ttf");

		TextRenderer* textRenderer = world->create <TextRenderer>();
		textRenderer->setFont(fontTest);
		textRenderer->transform.setLocalPosition({ -Context::getWindowWidth() / 2,0 });
		textRenderer->transform.setLocalScale({ 0.5f,0.5f });
		textRenderer->setText("OHAYOUUUUUU!!!!!");
		textRenderer->setText("YEEEEEEEhAw");

		TilemapRenderer* tilemapRen = world->create <TilemapRenderer>();
		Tilemap* tilemap = DBG_NEW Tilemap();
		tilemapRen->setTilemap(tilemap);
		tilemap->testSprite = sprite;
		tilemapRen->transform.setLocalPosition({ -50,-50 });

		Uint32 ticks = 0;
		while (!Context::getShouldClose())
		{
			ticks++;
			Context::tick();
			glm::vec2 mousePos = Input::getMousePos();
			mousePos = cam->screenToWorld(mousePos);

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

			//Check if the mouse is in the bounds of the tilemapRenderer
			int tileIndex = tilemapRen->worldToTile(mousePos);
			glm::vec2 tilePos = {0,0};
			if ( tileIndex != -1) {
				tilePos = tilemapRen->tileToPosition(tileIndex);
				Renderer::renderLine({ tilePos.x, tilePos.y }, { tilePos.x + tilemap->tileWidth,tilePos.y });
				Renderer::renderLine({ tilePos.x, tilePos.y }, { tilePos.x,tilePos.y + tilemap->tileHeight });
			}

			float speed = 50.0f;
			cam->transform.translate((movement * speed));
			Physics::tick();

			spriteRenderer->transform.setLocalScale({ sin((ticks * Context::getDeltaTime()) /10), 1 });
			spriteRenderer2->render();
			spriteRenderer->render();
			textRenderer->render();
			tilemapRen->render();
			
			
			//Renderer::renderLine(mousePos, mousePos, glm::vec4(255,0,0,255), 10.0f);

			bgfx::dbgTextPrintf(0, 3, 0x0f, "Camera X: %f Camera Y: %f", cam->transform.getPosition().x, cam->transform.getPosition().y);
			bgfx::dbgTextPrintf(0, 4, 0x0f, "Mouse X: %f Mouse Y: %f", mousePos.x, mousePos.y);
			bgfx::dbgTextPrintf(0, 5, 0x0f, "Tilemap Tile: %i", tileIndex);
			bgfx::dbgTextPrintf(0, 6, 0x0f, "Tilepos X: %f Tilepos Y: %f", tilePos.x, tilePos.y);

			Renderer::render();
			
		}
		delete(world);
		delete(tilemap);
		TextRenderer::destroy();
		SpriteRenderer::destroy();
		FileUtility::destroy();
		AssetManager::destroy();
		Context::quit();
	}
	

	_CrtDumpMemoryLeaks();
	return 0;
}
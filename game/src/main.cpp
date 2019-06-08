#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
#endif

#include "GoldEngine/Core/Context.h"
#include "GoldEngine/Core/FileUtility.h"
#include "GoldEngine/Core/Renderer.h"
#include "glm/vec2.hpp"
#include "SDL_events.h"
#include "SDL_pixels.h"
#include "Box2D/Box2D.h"
#include "GoldEngine/Core/Physics.h"


int main(){
	{
		ContextWindowParems cWinParems = { "Ayse why.", 1280, 720, 640, 360 };
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}

		glm::vec2 aysePos = { 100,100 };
		SDL_Color white = { 255,255,255,255 };

		SDL_Event e;
		SpriteData* ayse = FileUtility::loadSpriteData("assets/ayse.png");
		b2Body* ground = Physics::createBody(glm::vec2( cWinParems.renderWidth/2, 0 ), 
			glm::vec2(50,10 ), 0, 1, 0);
		b2Body* ball = Physics::createBody(glm::vec2(cWinParems.renderWidth / 2, cWinParems.renderHeight / 2 ), 
			glm::vec2(2,2 ), 0, 1, 1);

		while (!Context::getShouldClose())
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT) {
					Context::setShouldClose(true);
				}
			}
			Physics::tick();

			Renderer::clearRenderer(white);
			Renderer::renderSprite(aysePos, ayse);
			Renderer::renderb2Body(ground);
			Renderer::renderb2Body(ball);
			Renderer::render();
		}


		FileUtility::unloadSpriteData(ayse);
		Context::quit();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}
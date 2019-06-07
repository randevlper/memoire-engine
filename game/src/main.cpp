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
#include "SDL_events.h"


int main(){
	{
		ContextWindowParems cWinParems = { "Ayse why.", 1280, 720, 640, 360 };
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}

		SDL_Event e;
		SpriteData* ayse = FileUtility::loadSpriteData("assets/ayse.png");

		while (!Context::getShouldClose())
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT) {
					Context::setShouldClose(true);
				}
			}

			Renderer::clearRenderer(255, 255, 255, 255);
			Renderer::renderSprite(100, 100, ayse);
			Renderer::render();
		}


		FileUtility::unloadSpriteData(ayse);
		Context::quit();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}
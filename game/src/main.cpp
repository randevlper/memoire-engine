#include "GoldEngine/Core/Context.h"
#include "SDL_events.h"

int main(){
	ContextWindowParems cWinParems = { "Ayse why.", 1280, 720 };
	Context::init(&cWinParems);

	SDL_Event e;

	while (!Context::getShouldClose())
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				Context::setShouldClose(true);
			}
		}
	}

	Context::quit();
	return 0;
}
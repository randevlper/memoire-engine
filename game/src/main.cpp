#define STB_IMAGE_IMPLEMENTATION 1
#include "stb_image.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <cstdlib>
#include <iostream>
#include "Texture.h"

char WINDOW_NAME[] = { "Ayse please stop this." };

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

bool quit = false;

SDL_Event e;

SDL_Window* win;
SDL_Renderer* ren;

int init() {
	using std::cout;
	using std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	win = SDL_CreateWindow(WINDOW_NAME, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		cout << "SDL_CreateRenderer Error" << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
}

int main()
{
	if (init() == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	Texture ayse;
	ayse.loadFromFile("assets/ayse.png", ren);

	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_Rect boxRect = fillRect;
	boxRect.w = boxRect.w / 2;
	boxRect.h = boxRect.h / 2;
	boxRect.x = 0;

	Texture text;

	while (!quit) {

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			if (e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}

			if (e.key.keysym.sym == SDLK_LEFT) {

			}
		}

		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(ren);
		//Draw a line renderer, texture, portion of the tex, portion of the destRect
		//SDL_RenderCopy(ren, tex, nullptr, &fillRect);
		ayse.render(400, 400, ren);

		//Draw a box
		SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(ren, &boxRect);

		//Draw a line
		SDL_SetRenderDrawColor(ren,0, 0, 255, 255);
		SDL_RenderDrawLine(ren, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

		//Draw a dot
		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0x00, 0xFF);
		for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
			SDL_RenderDrawPoint(ren, SCREEN_WIDTH / 2, i);
		}

		SDL_RenderPresent(ren);
	}
		

	//stbi_image_free(ayse);
	//SDL_DestroyTexture(tex);
	ayse.unload();
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return EXIT_SUCCESS;
}
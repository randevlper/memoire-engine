#define STB_IMAGE_IMPLEMENTATION 1
#include "stb_image.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "entt/entt.hpp"
#include <cstdlib>
#include <iostream>

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

	int req_format = STBI_rgb_alpha;
	int width, height, orig_format;
	unsigned char *ayse = stbi_load("assets/ayse.png", &width, &height, &orig_format, req_format);
	if (ayse == nullptr) {
		SDL_Log("Loading image failed: %s", stbi_failure_reason());
	}
	int depth, pitch;
	Uint32 pixel_format;
	if (req_format == STBI_rgb) {
		depth = 24;
		pitch = 3 * width; // 3 bytes per pixel * pixels per row
		pixel_format = SDL_PIXELFORMAT_RGB24;
	}
	else { // STBI_rgb_alpha (RGBA)
		depth = 32;
		pitch = 4 * width;
		pixel_format = SDL_PIXELFORMAT_RGBA32;
	}
	SDL_Surface* ayse_surf = SDL_CreateRGBSurfaceWithFormatFrom((void*)ayse, width, height,
		depth, pitch, pixel_format);

	if (ayse_surf == NULL) {
		SDL_Log("Creating surface failed: %s", SDL_GetError());
		stbi_image_free(ayse);
	}

	SDL_Surface* bmp = SDL_LoadBMP("assets/grumpy-cat.bmp");
	if (bmp == nullptr) {
		SDL_Log("SDL_LoadBMP Error: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, ayse_surf);
	SDL_FreeSurface(ayse_surf);
	if (tex == nullptr) {
		SDL_Log("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_Rect boxRect = fillRect;
	boxRect.w = boxRect.w / 2;
	boxRect.h = boxRect.h / 2;
	boxRect.x = 0;


	while (!quit) {

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			if (e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(ren);
		//Draw a line renderer, texture, portion of the tex, portion of the destRect
		SDL_RenderCopy(ren, tex, nullptr, &fillRect);

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
		

	stbi_image_free(ayse);
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return EXIT_SUCCESS;
}
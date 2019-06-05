#define STB_IMAGE_IMPLEMENTATION 1
#include "stb_image.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <cstdlib>
#include <iostream>

int main()
{
	using std::cout;
	using std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 620, 387, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	SDL_Renderer* ren
		= SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		cout << "SDL_CreateRenderer Error" << SDL_GetError() << endl;
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
		cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, ayse_surf);
	SDL_FreeSurface(ayse_surf);
	if (tex == nullptr) {
		cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 20; i++) {
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, nullptr, nullptr);
		SDL_RenderPresent(ren);
		SDL_Delay(100);
	}

	stbi_image_free(ayse);
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return EXIT_SUCCESS;
}
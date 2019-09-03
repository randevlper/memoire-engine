#define STB_IMAGE_IMPLEMENTATION 1
#include "stb_image.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <cstdlib>
#include <iostream>
#include "Texture.h"
#include "entt/entt.hpp"
#include "cstdint"

struct position {
	float x;
	float y;
};

struct velocity {
	float dx;
	float dy;
};

char WINDOW_NAME[] = { "Ayse please stop this." };

//Ref Screen Size
int SCREEN_WIDTH = 320;
int SCREEN_HEIGHT = 180;

//Actual Screen Size
int AC_SCREEN_WIDTH = 1280;
int AC_SCREEN_HEIGHT = 720;

bool quit = false;

SDL_Event e;

SDL_Window* win;
SDL_Renderer* ren;
position camera;

int init() {
	using std::cout;
	using std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	win = SDL_CreateWindow(WINDOW_NAME, 100, 100, AC_SCREEN_WIDTH, AC_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void update(entt::registry &registry) {
	auto view = registry.view<position, velocity>();
	for (auto entity : view) {
		//gets only the components that are going to be used ...
		auto &vel = view.get<velocity>(entity);
		vel.dx = 0.1f;
		vel.dy = 0.1f;
	}
}

void update(std::uint32_t dt, entt::registry& registry) {
	registry.view<position, velocity>().each([dt](auto entity, auto & pos, auto & vel) {
		// gets all the components of the view at once ...
		pos.x += vel.dx * dt;
		pos.y += vel.dy * dt;

		if (pos.x > SCREEN_WIDTH) {
			pos.x = 0;
		}
		if (pos.y > SCREEN_HEIGHT) {
			pos.y = 0;
		}

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderDrawPoint(ren, pos.x, pos.y);
		});
}

int main(int argc, char** argv)
{
	if (init() == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	SDL_RenderSetScale(ren, AC_SCREEN_WIDTH/SCREEN_WIDTH, AC_SCREEN_HEIGHT /SCREEN_HEIGHT);
	SDL_Log("%d %d", AC_SCREEN_WIDTH / SCREEN_WIDTH, AC_SCREEN_HEIGHT / SCREEN_HEIGHT);

	Texture ayse;
	ayse.loadFromFile("assets/ayse.png", ren);

	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_Rect boxRect = fillRect;
	boxRect.w = boxRect.w / 2;
	boxRect.h = boxRect.h / 2;
	boxRect.x = 0;
	Texture text;

	camera = { 0,0,};

	entt::registry registry;
	std::uint32_t dt = 16;

	for (size_t i = 0; i < 1000; i++)
	{
		auto entity = registry.create();
		registry.assign<position>(entity, i * 1.f, i * 1.f);
		registry.assign<velocity>(entity, i * .1f, i * .1f);
	}

	while (!quit) {

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			if (e.key.keysym.sym == SDLK_w) {
				camera.y -= 5;
			}
			if (e.key.keysym.sym == SDLK_s) {
				camera.y += 5;
			}
			if (e.key.keysym.sym == SDLK_d) {
				camera.x += 5;
			}
			if (e.key.keysym.sym == SDLK_a) {
				camera.x -= 5;
			}
		}

		//update entities
		update(registry);

		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(ren);
		//Update entities

		SDL_Point points[8];
		int count = 0;

		//Draw Box2D objects
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderDrawLines(ren, points, count);

		//Draw Box2D objects
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderDrawLines(ren, points, count);


		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
		//Draw a line renderer, texture, portion of the tex, portion of the destRect
		//SDL_RenderCopy(ren, tex, nullptr, &fillRect);
		ayse.render(0 - camera.x, 0 - camera.y, ren, nullptr);
		ayse.render(0 - camera.x, 200 - camera.y, ren, nullptr);
		//ayse.render(0, 200, ren, &camera);
		//ayse.render(0, 300, ren, &camera);

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

		//Draw entities as dots
		update(dt, registry);

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
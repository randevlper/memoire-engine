#pragma once
#include "SDL_stdinc.h"
struct SDL_Rect;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class Texture
{
public:
	//Initialization
	Texture();

	//Deallocates memory
	~Texture();

	bool loadFromFile(char path[], SDL_Renderer* renderer);

	void unload();

	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = nullptr);

	int getWidth();
	int getHeight();

private:
	static bool test;
	unsigned char* pixels;
	SDL_Texture* texture;
	SDL_Surface* surface;
	int width;
	int height;
	int orig_format;
	int depth, pitch;
	Uint32 pixel_format;
	int req_format;
};
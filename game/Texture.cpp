#include "Texture.h"
#include "stb_image.h"
#include "SDL.h"

Texture::Texture()
{
	width = height = orig_format = depth = pitch = 0;
	pixel_format = 0;
	req_format = STBI_rgb_alpha;
	surface = nullptr; 
	texture = nullptr;
	pixels = nullptr;
}

Texture::~Texture()
{
	unload();
}

bool Texture::loadFromFile(char path[], SDL_Renderer* renderer)
{
	if (pixels != nullptr) {
		unload();
	}

	pixels = stbi_load(path, &width, &height, &orig_format, req_format);
	if (pixels == nullptr) {
		SDL_Log("Loading image failed: %s", stbi_failure_reason());
		return false;
	}
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
	surface = SDL_CreateRGBSurfaceWithFormatFrom((void*)pixels, width, height,
		depth, pitch, pixel_format);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return true;
}

void Texture::unload()
{
	if (pixels != nullptr) {
		stbi_image_free(pixels);
		pixels = nullptr;
	}

	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, width, height };
	if (clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

int Texture::getWidth()
{
	return 0;
}

int Texture::getHeight()
{
	return 0;
}

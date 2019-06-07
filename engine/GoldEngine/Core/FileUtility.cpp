#include "GoldEngine/Core/FileUtility.h"
#include "GoldEngine/Core/Context.h"
#include "stb_image.h"
#include "SDL.h"

SpriteData* FileUtility::loadSpriteData(char path[])
{
	SpriteData *spriteData = new SpriteData();
	int req_format = STBI_rgb_alpha;
	spriteData->pixels = stbi_load(path, &spriteData->width, &spriteData->height, 
		&spriteData->orig_format, req_format);
	if (spriteData->pixels == nullptr) {
		SDL_Log("Loading image failed: %s", stbi_failure_reason());
		delete(spriteData);
		return nullptr;
	}
	if (req_format == STBI_rgb) {
		spriteData->depth = 24;
		spriteData->pitch = 3 * spriteData->width; // 3 bytes per pixel * pixels per row
		spriteData->pixel_format = SDL_PIXELFORMAT_RGB24;
	}
	else { // STBI_rgb_alpha (RGBA)
		spriteData->depth = 32;
		spriteData->pitch = 4 * spriteData->width;
		spriteData->pixel_format = SDL_PIXELFORMAT_RGBA32;
	}

	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(spriteData->pixels, spriteData->width, spriteData->height,
		spriteData->depth, spriteData->pitch, spriteData->pixel_format);
	spriteData->texture = SDL_CreateTextureFromSurface(Context::getRenderer(), surface);
	SDL_FreeSurface(surface);

	return spriteData;
}

void FileUtility::unloadSpriteData(SpriteData* spriteData)
{
	if (spriteData->pixels != nullptr) {
		stbi_image_free(spriteData->pixels);
		spriteData->pixels = nullptr;
	}

	if (spriteData->texture != nullptr) {
		SDL_DestroyTexture(spriteData->texture);
		spriteData->texture = nullptr;
	}
}

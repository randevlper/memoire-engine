#include "GoldEngine/Core/FileUtility.h"
#include "GoldEngine/Data/SpriteData.h"
#include "GoldEngine/Core/Context.h"
#include "GoldEngine/Tools/aseprite.h"
#include "stb_image.h"
#include "SDL.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


SpriteData* FileUtility::loadSpriteData(char path[])
{
	SpriteData *spriteData = DBG_NEW SpriteData();
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

	delete(spriteData);
}

AseData* FileUtility::loadAse(char path[])
{
	Aseprite::AsepriteFile* file = new Aseprite::AsepriteFile(path);
	AseData* data = new AseData();
	data->aseFile = file;
	SDL_Surface* surface;

	for (const auto& chunk : file->frames[0].chunks) {
		if (chunk.type == Aseprite::AseChunkType::CEL_0x2005) {
			const auto& celChunk = std::get<Aseprite::AseCelChunk>(chunk.data);
			surface = SDL_CreateRGBSurfaceWithFormatFrom((unsigned char*)celChunk.pixels.data(), celChunk.width, celChunk.height, 32, 4 * celChunk.width, SDL_PIXELFORMAT_RGBA32);
			data->texture = SDL_CreateTextureFromSurface(Context::getRenderer(), surface);
			data->width = celChunk.width;
			data->height = celChunk.height;
		}
	}
	SDL_FreeSurface(surface);
	return data;
}

void FileUtility::unloadAse(AseData* data)
{
	delete(data->aseFile);
	delete(data);
}



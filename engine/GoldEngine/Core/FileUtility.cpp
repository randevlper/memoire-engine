#include "GoldEngine/Core/FileUtility.h"
#include "GoldEngine/Data/SpriteData.h"
#include "GoldEngine/Data/AseData.h"
#include "GoldEngine/Core/Context.h"
#include "GoldEngine/Tools/aseprite.h"
#include "stb_image.h"
#include "SDL.h"
#include <vector>

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
	SDL_Surface* surface;
	SDL_Texture* texture;

	//Get Frames
	data->frames.resize(file->frames.size());
	for (size_t i = 0; i < file->frames.size(); i++){
		data->frames[i].frameDuration = file->frames[i].frameDuration;
		//Get and Setup Sprites
		for (const auto& chunk : file->frames[i].chunks) {
			if (chunk.type == Aseprite::AseChunkType::CEL_0x2005) {
				const auto& celChunk = std::get<Aseprite::AseCelChunk>(chunk.data);

				surface = SDL_CreateRGBSurfaceWithFormatFrom(
					(unsigned char*)celChunk.pixels.data(),
					celChunk.width, celChunk.height, 32,
					4 * celChunk.width, SDL_PIXELFORMAT_RGBA32);
				texture = SDL_CreateTextureFromSurface(Context::getRenderer(), surface);

				SDL_FreeSurface(surface);

				data->frames[i].sprites.push_back(AseSprite(texture, celChunk.width,
					celChunk.height, celChunk.x, celChunk.y, celChunk.layerIndex));
			}
		}
	}

	//Setup Animations
	for (size_t i = 0; i < file->frames.size(); i++) {
		for (const auto& chunk : file->frames[i].chunks) {
			if (chunk.type == Aseprite::AseChunkType::FRAME_TAGS_0x2018) {
				const auto& celChunk = std::get<Aseprite::AseFrameTagChunk>(chunk.data);
				for (const auto& tag : celChunk.tags) {
					AseAnimation a(tag.tagName.toString());
					for (size_t i = tag.fromFrame; i <= tag.toFrame; i++){
						a.frames.push_back(&data->frames[i]);
					}
					data->animations.push_back(AseAnimation(a));
				}
			}
		}
	}

	delete(file);
	return data;
}

void FileUtility::unloadAse(AseData* data)
{
	delete(data);
}



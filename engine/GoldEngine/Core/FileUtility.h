#pragma once
#define STB_IMAGE_IMPLEMENTATION 1
struct SDL_Texture;

struct SpriteData
{
	unsigned char* pixels;
	int width, height, orig_format, req_format;
	int depth, pitch, pixel_format;
	SDL_Texture* texture;
};

class FileUtility
{
public:
	static SpriteData* loadSpriteData(char path[]);
	static void unloadSpriteData(SpriteData* spriteData);
	//LoadSprite

private:

};
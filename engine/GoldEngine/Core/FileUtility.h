#pragma once
#define STB_IMAGE_IMPLEMENTATION 1
struct SpriteData;

class FileUtility
{
public:
	static SpriteData* loadSpriteData(char path[]);
	static void unloadSpriteData(SpriteData* spriteData);
	//LoadSprite

private:

};
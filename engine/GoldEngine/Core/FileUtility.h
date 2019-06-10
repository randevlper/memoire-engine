#pragma once
#define STB_IMAGE_IMPLEMENTATION 1
struct SpriteData;
struct AseData;

class FileUtility
{
public:
	static SpriteData* loadSpriteData(char path[]);
	static void unloadSpriteData(SpriteData* spriteData);
	static AseData* loadAse(char path[]);
	static void unloadAse(AseData* data);
	//LoadSprite

private:
};
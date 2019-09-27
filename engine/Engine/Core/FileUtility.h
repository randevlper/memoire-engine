#pragma once
#define STB_IMAGE_IMPLEMENTATION 1
struct SpriteData;
struct AseData;

namespace bgfx {
	struct ShaderHandle;
	struct ProgramHandle;
}

class FileUtility
{
public:
	static SpriteData* loadSpriteData(char path[]);
	static void unloadSpriteData(SpriteData* spriteData);
	static bgfx::ShaderHandle loadShader(const char* FILENAME);
	static bgfx::ProgramHandle loadProgram(const char* FILEA, const char* FILEB);

	static AseData* loadAse(char path[]);
	static void unloadAse(AseData* data);
	//LoadSprite

private:
};
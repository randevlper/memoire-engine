#pragma once
#define STB_IMAGE_IMPLEMENTATION 1
struct SpriteData;
struct AseData;

namespace bgfx {
	struct ShaderHandle;
	struct ProgramHandle;
}

namespace bx {
	struct AllocatorI;
	struct FileReaderI;
}

class FileUtility
{
public:
	static SpriteData* loadSpriteData(char path[]);
	static void unloadSpriteData(SpriteData* spriteData);
	static bgfx::ShaderHandle loadShader(const char* FILENAME);
	static bgfx::ProgramHandle loadProgram(const char* vert, const char* frag);

	static AseData* loadAse(char path[]);
	static void unloadAse(AseData* data);
	//LoadSprite

	static bx::AllocatorI* getAllocator();
	static bx::AllocatorI* g_allocator;
private:
	static bx::AllocatorI* getDefaultAllocator();

	
	static bx::FileReaderI* s_fileReader;
	
};
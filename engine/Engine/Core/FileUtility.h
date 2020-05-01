#pragma once
#include <string>

struct AseData;

#include "bimg/bimg.h"

namespace bgfx {
	struct ShaderHandle;
	struct ProgramHandle;
	struct TextureInfo;
	struct TextureHandle;
}

namespace bx {
	struct AllocatorI;
	struct FileReaderI;
}

class Sprite;

class FileUtility
{
public:
	static bgfx::ShaderHandle loadShader(const char* FILENAME);
	static bgfx::ProgramHandle loadProgram(const char* vert, const char* frag);

	static AseData* loadAse(char path[]);
	static void unloadAse(AseData* data);
	//LoadSprite

	static void* load(bx::FileReaderI* _reader, bx::AllocatorI* _allocator, const char* _filePath, unsigned int* _size);
	static void unload(void* _ptr);
	static Sprite* loadTexture(bx::FileReaderI* _reader, const char* _filePath, unsigned long long _flags, 
		unsigned char _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation);
	static Sprite* loadTexture(const char* _name, unsigned long long _flags, 
		unsigned char _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation);
	
	static bx::AllocatorI* getAllocator();
	static bx::FileReaderI* getFileReader();

	static std::string loadTextFile(const char* filePath);
	static void writeStringFile(const char* filePath, std::string &value);

	static void destroy();
private:

	static bx::AllocatorI* getDefaultAllocator();
	static bx::AllocatorI* g_allocator;
	static bx::FileReaderI* s_fileReader;
	static void imageReleaseCb(void* _ptr, void* _userData);
	
};
#pragma once
#define STB_IMAGE_IMPLEMENTATION 1
struct SpriteData;
struct AseData;

#include "bx/bx.h"
#include "bx/file.h"

#include "bimg/bimg.h"
#include "bgfx/bgfx.h"

class FileReader : public bx::FileReader
{
	typedef bx::FileReader super;

public:
	virtual bool open(const bx::FilePath& _filePath, bx::Error* _err) override
	{
		//s_currentDir.set("");
		//String filePath(s_currentDir);
		//filePath.append(_filePath);
		return super::open("", _err);
	}
};

class FileUtility
{
public:
	static SpriteData* loadSpriteData(char path[]);
	static void unloadSpriteData(SpriteData* spriteData);

	static AseData* loadAse(char path[]);
	static void unloadAse(AseData* data);

	static void init();
	//LoadSprite


	static void* load(bx::FileReaderI* _reader, bx::AllocatorI* _allocator, const char* _filePath, uint32_t* _size);
	static void unload(void* _ptr){
		BX_FREE(getAllocator(), _ptr);
	}

	static bgfx::TextureHandle loadTexture(bx::FileReaderI* _reader, const char* _filePath, uint64_t _flags, uint8_t _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation);
	static bgfx::TextureHandle loadTexture(const char* _name, uint64_t _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE, uint8_t _skip = 0, bgfx::TextureInfo * _info = NULL, bimg::Orientation::Enum * _orientation = NULL);
	static void imageReleaseCb(void* _ptr, void* _userData);
private:
	static bx::AllocatorI* getDefaultAllocator() {
		BX_PRAGMA_DIAGNOSTIC_PUSH();
		BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 's_allocator' hides global declaration
		BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");
		static bx::DefaultAllocator s_allocator;
		return &s_allocator;
		BX_PRAGMA_DIAGNOSTIC_POP();
	}

	static bx::FileReaderI* getFileReader() {
		return s_fileReader;
	}
	static bx::AllocatorI* getAllocator(){
		if (NULL == g_allocator){
			g_allocator = getDefaultAllocator();
		}
		return g_allocator;
	}

	static bx::AllocatorI* g_allocator;
	static bx::FileReaderI* s_fileReader;
};


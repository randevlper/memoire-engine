#include "Engine/Core/FileUtility.h"

#include <vector>
#include <iostream>
#include <fstream>

#include <filesystem>

#include <stb_image.h>
#include <SDL.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

//#include <bimg/bimg.h>
#include <bimg/decode.h>

#include <bx/bx.h>
#include <bx/file.h>
#include <bx/readerwriter.h>
#include <bx/string.h>
#include <bx/allocator.h>

#include "Engine/Data/AseData.h"
#include "Engine/Core/Context.h"
#include "Engine/Tools/aseprite.h"
#include "Engine/Utilities/FileReader.h"
#include "Engine/AssetManagement/Sprite.h"

#include "Engine/Utilities/DebugMemory.h"
#include "Engine/Utilities/Debug.h"

bx::AllocatorI* FileUtility::g_allocator = getDefaultAllocator();
bx::FileReaderI* FileUtility::s_fileReader = BX_NEW(g_allocator, FileReader);

bgfx::ShaderHandle FileUtility::loadShader(const char* FILENAME)
{
	FILE* file = fopen(FILENAME, "rb");
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	const bgfx::Memory* mem = bgfx::alloc(fileSize + 1);
	fread(mem->data, 1, fileSize, file);
	mem->data[mem->size - 1] = '\0';
	fclose(file);

	return bgfx::createShader(mem);
}

bgfx::ProgramHandle FileUtility::loadProgram(const char* vert, const char* frag)
{
	return bgfx::createProgram(loadShader(vert), loadShader(frag), true);
}

AseData* FileUtility::loadAse(char path[])
{
	Aseprite::AsepriteFile* file = DBG_NEW Aseprite::AsepriteFile(path);
	AseData* data = DBG_NEW AseData();
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
				//texture = SDL_CreateTextureFromSurface(Context::getRenderer(), surface);

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

bx::AllocatorI* FileUtility::getDefaultAllocator()
{
	BX_PRAGMA_DIAGNOSTIC_PUSH();
	BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 's_allocator' hides global declaration
	BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");
	static bx::DefaultAllocator s_allocator;
	return &s_allocator;
	BX_PRAGMA_DIAGNOSTIC_POP();
}

void FileUtility::imageReleaseCb(void* _ptr, void* _userData)
{
	BX_UNUSED(_ptr);
	bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
	bimg::imageFree(imageContainer);
}

void* FileUtility::load(bx::FileReaderI* _reader, bx::AllocatorI* _allocator, const char* _filePath, unsigned int* _size)
{
	if (bx::open(_reader, _filePath))
	{
		uint32_t size = (uint32_t)bx::getSize(_reader);
		void* data = BX_ALLOC(_allocator, size);
		bx::read(_reader, data, size);
		bx::close(_reader);
		if (NULL != _size)
		{
			*_size = size;
		}
		return data;
	}
	else
	{
		//DBG("Failed to open: %s.", _filePath);
	}

	if (NULL != _size)
	{
		*_size = 0;
	}

	return NULL;
}

void FileUtility::unload(void* _ptr)
{
	BX_FREE(getAllocator(), _ptr);
}

Sprite* FileUtility::loadTexture(bx::FileReaderI* _reader, const char* _filePath, unsigned long long _flags, unsigned char _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation)
{
	BX_UNUSED(_skip);
	Sprite* sprite = nullptr;
	bgfx::TextureHandle spriteHandle = BGFX_INVALID_HANDLE;


	uint32_t size;
	void* data = load(_reader, getAllocator(), _filePath, &size);
	if (NULL != data)
	{
		bimg::ImageContainer* imageContainer = bimg::imageParse(getAllocator(), data, size);

		if (NULL != imageContainer)
		{
			if (NULL != _orientation)
			{
				*_orientation = imageContainer->m_orientation;
			}

			const bgfx::Memory* mem = bgfx::makeRef(
				imageContainer->m_data
				, imageContainer->m_size
				, imageReleaseCb
				, imageContainer
			);

			if (imageContainer->m_cubeMap)
			{
				spriteHandle = bgfx::createTextureCube(
					uint16_t(imageContainer->m_width)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
				);
			}
			else if (1 < imageContainer->m_depth)
			{
				spriteHandle = bgfx::createTexture3D(
					uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, uint16_t(imageContainer->m_depth)
					, 1 < imageContainer->m_numMips
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
				);
			}
			else if (bgfx::isTextureValid(0, false, imageContainer->m_numLayers, bgfx::TextureFormat::Enum(imageContainer->m_format), _flags))
			{
				spriteHandle = bgfx::createTexture2D(
					uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
				);
			}

			if (bgfx::isValid(spriteHandle))
			{
				bgfx::setName(spriteHandle, _filePath);
				sprite = DBG_NEW Sprite(
					spriteHandle
					, uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
				);
			}

			if (NULL != _info)
			{
				bgfx::calcTextureSize(
					*_info
					, uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, uint16_t(imageContainer->m_depth)
					, imageContainer->m_cubeMap
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
				);
			}
		}
		unload(data);
	}

	return sprite;
}

Sprite* FileUtility::loadTexture(const char* _name, unsigned long long _flags, unsigned char _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation)
{
	return loadTexture(getFileReader(), _name, _flags, _skip, _info, _orientation);
}

bx::AllocatorI* FileUtility::getAllocator()
{
	if (NULL == g_allocator){
		g_allocator = getDefaultAllocator();
	}
	return g_allocator;
}

bx::FileReaderI* FileUtility::getFileReader()
{
	return s_fileReader;
}

std::string FileUtility::loadTextFile(const char* filePath)
{
	std::ifstream input(filePath);
	if (input.is_open()) {
		std::string value;
		value.assign((std::istreambuf_iterator<char>(input)),
			(std::istreambuf_iterator<char>()));
		input.close();
		return value;
	}

	return std::string();
}

void FileUtility::writeStringFile(const char* path, const char* fileName, std::string &value)
{
	std::string msg;

	if (path != nullptr) {
		if (!std::filesystem::exists(path)) {
			//Create directory
			msg = "[FileUtility] Creating: ";
			msg += path;
			Debug::Log(msg);
			if (!std::filesystem::create_directory(path)) {
				msg = "[FileUtility] Directory could not be created! |";
				msg += path;
				Debug::Log(msg);
				return;
			}
		}
	}

	std::string fullPath;
	if (path != nullptr) {
		fullPath.append(path);
	}
	fullPath.append(fileName);

	std::ofstream output(fullPath);
	if (output.is_open()) {
		output << value;
		output.close();
	}
	else {
		msg = "[FileUtility] File could not be written! ";
		msg += fullPath;
		Debug::Log(msg);
	}
}

bool FileUtility::loadJson(const char* path, nlohmann::json& j)
{
	if (std::filesystem::exists(path)) {
		std::ifstream fileStream(path);
		fileStream >> j;
		fileStream.close();
	}
	else {
		return false;
	}
	return true;
}
void FileUtility::destroy()
{
	BX_DELETE(g_allocator, s_fileReader);
}

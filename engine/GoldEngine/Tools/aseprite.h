#pragma once
#include <cstdint>
#include <iosfwd>
#include <vector>

namespace Aseprite {
	static bool tinf_initialized = false;

	struct AseChunk;

	using BYTE = uint8_t;
	using WORD = uint16_t;
	using SHORT = int16_t;
	using DWORD = uint32_t;
	using LONG = int32_t;
	using FIXED = int32_t; // convert 16.16 fixed to double: x / 65536

	template<typename OutData>
	bool getHeadPart(std::ifstream& stream, OutData& data) {
		stream.read((char*)& data, sizeof(OutData));
		return stream.good();
	}

	struct AseHeader
	{
		DWORD fileSize;
		WORD magicNumber; //(0xA5E0)
		WORD frames;
		WORD width;
		WORD height;
		WORD bitDepth; //bits per pixel, 32 = RGBA, 16 = Grayscale, 8 = Indexed
		DWORD flags;
		WORD speed; //milliseconds between frame, deprecated use frame duration
		DWORD setZero0; //Set be zero
		DWORD setZerp1; //Set be zero
		BYTE transparentIndex;// palette index of transparent color in 8 bit sprites
		BYTE stuff2[3]; //ignore
		WORD colorsCount; //For old sprites 0 = 256
		BYTE pixelWidth; //if zero aspect is 1:1
		BYTE pixelHeight;
		BYTE reserved[92];

		bool read(std::ifstream& s);
		void print();
	};

	enum PixelType{
		RGBA, Grayscale, Indexed
	};

	struct AseFrame
	{
		DWORD bytes;
		WORD magicNumber; //(always 0xF1FA)
		WORD numberChunksOLD; //Old field which specifies the number of "chunks"
						   //in this frame.If this value is 0xFFFF, we might
						   //have more chunks to read in this frame
						   //(so we have to use the new field)
		WORD frameDuration;
		BYTE future[2]; //set to zero;
		DWORD numberChunksNEW; //New field which specifies the number of "chunks"
							   //in this frame(if this is 0, use the old field)
		std::vector<AseChunk> chunks;

		bool read(std::ifstream& s, PixelType  pixelType);
	};
	
	class AsepriteFile
	{
	public:
		AseHeader header;
		std::vector<AseFrame> frames;

		AsepriteFile(char filename[]);
		~AsepriteFile();
	};
}
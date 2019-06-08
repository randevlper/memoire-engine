#pragma once
#include <cstdint>
#include <iosfwd>

namespace Aseprite {
	static bool tinf_initialized = false;

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

	struct AsepriteHeader
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

	struct AsepriteFrame
	{

	};
	
	class AsepriteFile
	{
	public:
		AsepriteHeader header;

		AsepriteFile(char filename[]);
		~AsepriteFile();

		//

	private:

	};
}
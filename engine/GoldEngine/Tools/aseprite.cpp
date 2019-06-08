#include "aseprite.h"
#include "asepriteChunks.h"
#include <fstream>
#include <iostream>
#include "tinf.h";


namespace Aseprite {
	AsepriteFile::AsepriteFile(char filename[])
	{
		header = { 0 };
		std::ifstream file(filename, std::ios::in | std::ios::binary);
		if (!file.good()) {
			std::cout << "File " << filename << " not good!\n" << std::endl;
			file.close();
			return;
		}
		else {
			std::cout << "File " << filename << " found!\n" << std::endl;
		}

		if (!tinf_initialized) {
			tinf_init();
			tinf_initialized = true;
		}

		if (header.read(file)) {
			header.print();
			PixelType pixelFormat = RGBA;
			switch (header.bitDepth){
			case 8:
				pixelFormat = Indexed; break;
			case 16:
				pixelFormat = Grayscale; break;
			case 32:
				pixelFormat = RGBA; break;
			default:
				std::cout << "PixelFormat is invalid." << pixelFormat  << std::endl; break;
			}
			frames.resize(header.frames);
			for (size_t i = 0; i < header.frames && file.good(); i++){
				if (!frames[i].read(file, pixelFormat)) {
					std::cout << " Failed to read FRAME " << i << " in " << filename << " ...stopping.\n";
					break;
				}
			}
		}

		file.close();
	}

	AsepriteFile::~AsepriteFile()
	{

	}


	bool AseHeader::read(std::ifstream& s)
	{
		return
			getHeadPart(s, fileSize) &&
			getHeadPart(s, magicNumber) &&
			getHeadPart(s, frames) &&
			getHeadPart(s, width) &&
			getHeadPart(s, height) &&
			getHeadPart(s, bitDepth) &&
			getHeadPart(s, flags) &&
			getHeadPart(s, speed) &&
			getHeadPart(s, setZero0) &&
			getHeadPart(s, setZerp1) &&
			getHeadPart(s, transparentIndex) &&
			getHeadPart(s, stuff2) &&
			getHeadPart(s, colorsCount) &&
			getHeadPart(s, pixelWidth) &&
			getHeadPart(s, pixelHeight) &&
			getHeadPart(s, reserved);
	}

	void AseHeader::print()
	{
		std::cout << "HEADER\n"
			"fileSize           :" << fileSize << "\n"
			"magicNumber        :" << std::hex << magicNumber << std::dec << "\n"
			"frames             :" << frames << "\n"
			"width              :" << width << "\n"
			"height             :" << height << "\n"
			"bitDepth           :" << bitDepth << "\n"
			"flags              :" << flags << "\n"
			"speed              :" << speed << "\n"
			"stuff_0            :" << setZero0 << "\n"
			"stuff_1            :" << setZerp1 << "\n"
			"transparentIndex   :" << (int)transparentIndex << "\n"
			"stuff_2            :(len)" << sizeof(stuff2) << "\n"
			"colorsCount        :" << colorsCount << "\n"
			"pixelWidth         :" << (int)pixelWidth << "\n"
			"pixelHeight        :" << (int)pixelHeight << "\n"
			"reserved           :(len)" << sizeof(reserved) << "\n";
	}

	bool AseFrame::read(std::ifstream& s, PixelType pixelType)
	{
		bool result =
			getHeadPart(s, bytes) &&
			getHeadPart(s, magicNumber) &&
			getHeadPart(s, numberChunksOLD) &&
			getHeadPart(s, frameDuration) &&
			getHeadPart(s, future) &&
			getHeadPart(s, numberChunksNEW);

		if (false) {
			if (numberChunksNEW != 0) {
				chunks.reserve(numberChunksNEW);
			}
			else {
				chunks.reserve(numberChunksOLD);
			}

			for (size_t i = 0; i < numberChunksNEW != 0 ? numberChunksNEW : numberChunksOLD; i++)
			{
				DWORD size = 0;
				WORD type = 0;
				constexpr size_t chunkHeaderSize = sizeof(size) + sizeof(type);
				auto p = s.tellg();
				result = result && getHeadPart(s, size) && getHeadPart(s, type);
				auto p2 = s.tellg();
				std::cout << std::hex << "0x" << p2 << ":DEBUG Chunk: size: " << size << " type: " << type << std::dec << "\n";
				switch (type)
				{
				case PALETTE_OLD_0x0004:
					break;
				//case PALETTE_OLD_0x0011:
				//	break;
				//case LAYER_0x2004:
				//	break;
				//case CEL_0x2005:
				//	break;
				//case CEL_EXTRA_0x2006:
				//	break;
				//case MASK_0x2016:
				//	break;
				//case PATH_0x2017:
				//	break;
				//case FRAME_TAGS_0x2018:
				//	break;
				//case PALETTE_0x2019:
				//	break;
				//case USER_DATA_0x2020:
				//	break;
				//case SLICE_0x2022:
				//	break;
				default:
					//std::cout << "^ not parsed\n";
					s.seekg(size + p); // skip data
				}
				result = result && s.good();
			}
		}

		return result;
	}
}



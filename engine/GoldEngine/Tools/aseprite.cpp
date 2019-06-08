#include "aseprite.h"
#include <fstream>
#include <iostream>
#include "tinf.h";

namespace Aseprite {
	AsepriteFile::AsepriteFile(char filename[])
	{
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

		header = {};
		header.read(file);

	}

	AsepriteFile::~AsepriteFile()
	{

	}


	bool AsepriteHeader::read(std::ifstream& s)
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

	void AsepriteHeader::print()
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
}



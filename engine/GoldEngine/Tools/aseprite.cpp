#include "aseprite.h"
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
				else {
					frames[i].print();
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

		if (result) {
			size_t chunkCount = 0;
			if (numberChunksNEW != 0) {
				chunks.reserve(numberChunksNEW);
				chunkCount = numberChunksNEW;
			}
			else {
				chunks.reserve(numberChunksOLD);
				chunkCount = numberChunksOLD;
			}

			for (size_t i = 0; i < chunkCount && result; i++)
			{
				DWORD size = 0;
				WORD type = 0;
				constexpr size_t chunkHeaderSize = sizeof(size) + sizeof(type);
				auto p = s.tellg();
				result = result && getHeadPart(s, size) && getHeadPart(s, type);
				auto p2 = s.tellg();
				std::cout << std::hex << "0x" << p2 << ":DEBUG Chunk: size: " << (int)size << " type: " << type << std::dec << "\n";
				switch (type)
				{
				case PALETTE_OLD_0x0004:
					chunks.emplace_back(AsePaletteOldChunk(s) , type);
					break;
				case PALETTE_OLD_0x0011:
					chunks.emplace_back(AsePaletteOldChunk(s), type);
					break;
				case LAYER_0x2004:
					chunks.emplace_back(AseLayerChunk(s), type);
					break;
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
				case PALETTE_0x2019:
					chunks.emplace_back(AsePaletteChunk(s), type);
					break;
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
	void AseFrame::print()
	{
		std::cout << "Frame" << std::endl <<
			"Bytes             :" << bytes << std::endl <<
			"Magic Number      :" << std::hex << magicNumber << std::dec << std::endl <<
			"Number Chunks OLD :" << numberChunksOLD << std::endl <<
			"Frame Duration    :" << frameDuration << std::endl <<
			"future (len)      :" << sizeof(future) << std::endl <<
			"Number Chunks NEW :" << numberChunksNEW << std::endl << std::endl;
	}

	AsePaletteOldChunk::AsePaletteOldChunk(std::ifstream& s)
	{
		read(s);
	}

	bool AsePaletteOldChunk::read(std::ifstream& s)
	{
		bool result = getHeadPart(s, numPackets);
		WORD lastIndex = 0;
		
		if (result) {
			packets.resize(numPackets);
			for (WORD i = 0; i < numPackets; i++) {
				result = getHeadPart(s, packets[i].numPalletesToSkip) &&
					getHeadPart(s, packets[i].colorsCount);
				packets[i].colorsCount == 0 ? 256 : packets[i].colorsCount;

				if (!result) {
					return false;
				}

				lastIndex += packets[i].numPalletesToSkip;
				for (WORD c = 0; c < packets[i].colorsCount; c++) {
					if (lastIndex > 255) { return false; };
					COLOR &color = packets[i].colors[c];
					result = result &&
						getHeadPart(s, color.r) &&
						getHeadPart(s, color.g) &&
						getHeadPart(s, color.b);
				}
			}
		}
		print();
		return true;
	}

	void AsePaletteOldChunk::print()
	{
		std::cout << "Chunk: Old palette chunk (0x0004)" << std::endl <<
			"NumPackets: " << numPackets << std::endl;

		for (size_t i = 0; i < numPackets; i++)
		{
			std::cout <<
				"Packet " << i << ":" << std::endl <<
				"NumPalletesToSkip :" << packets[i].numPalletesToSkip << std::endl;

			for (size_t c = 0; c < packets[i].colorsCount; c++)
			{
				std::cout << "Color :" << c << std::endl <<
					packets[i].colors[c].r << 
					packets[i].colors[c].g << 
					packets[i].colors[c].b << std::endl;
			}
		}
	}

	AseChunk::AseChunk(chunkType&& data, WORD type) : 
		data(std::move(data)),
		type(type)
	{

	}
	AsePaletteChunk::AsePaletteChunk(std::ifstream& s)
	{
		read(s);
	}
	bool AsePaletteChunk::read(std::ifstream& s)
	{
		bool result =
			getHeadPart(s, paletteSize) &&
			getHeadPart(s, firstColor) &&
			getHeadPart(s, lastColor) &&
			getHeadPart(s, future);

		if (!result) { return result; };
		paletteEntries.resize(paletteSize);
		for (DWORD i = firstColor; i <= lastColor && result; i++) {
			if (i > 255) { return false; }
			COLOR& c = paletteEntries[i].color;

			result = result &&
				getHeadPart(s, paletteEntries[i].entryFlags) &&
				getHeadPart(s, c.r) &&
				getHeadPart(s, c.g) &&
				getHeadPart(s, c.b) &&
				getHeadPart(s, c.a);
			if (result && paletteEntries[i].entryFlags == 0x1) {
				result = result && paletteEntries[i].colorName.read(s);
			}
		}
		print();
		return true;
	}
	void AsePaletteChunk::print()
	{
		std::cout << "Palette Chunk (0x2019)" << std::endl <<
			"Palette Size :" << paletteSize << std::endl <<
			"First Color :" << firstColor << std::endl <<
			"Last Color :" << lastColor << std::endl <<
			"Future (len):" << sizeof(future) << std::endl;

		for (size_t i = 0; i < paletteSize; i++)
		{
			std::cout << 
				"Color " << i << ":" << 
				paletteEntries[i].color.r <<
				paletteEntries[i].color.g <<
				paletteEntries[i].color.b << 
				paletteEntries[i].color.a << std::endl;
		}
	}
	bool STRING::read(std::ifstream& s)
	{
		bool result = getHeadPart(s, length);
		if (!result) {
			return result;
		}
		characters.resize(length);
		for (size_t i = 0; i < length && result; i++)
		{
			result = result && getHeadPart(s, characters[i]);
		}
		return result;
	}
	std::string STRING::toString()
	{
		return std::string(reinterpret_cast<const char*>(&characters[0]), characters.size());
	}
	AseLayerChunk::AseLayerChunk(std::ifstream& s)
	{
		read(s);
	}
	bool AseLayerChunk::read(std::ifstream& s)
	{
		bool result =
			getHeadPart(s, flags) &&
			getHeadPart(s, layerType) &&
			getHeadPart(s, layerChildLevel) &&
			getHeadPart(s, width) &&
			getHeadPart(s, height) &&
			getHeadPart(s, blendMode) &&
			getHeadPart(s, opacity) &&
			getHeadPart(s, unused) &&
			name.read(s);
		print();
		return result;
	}
	void AseLayerChunk::print()
	{
		std::cout << "Layer Chunk (0x2004)" << std::endl <<
			"flags           :" << flags << std::endl <<
			"layerType       :" << layerType << std::endl <<
			"layerChildLevel :" << layerChildLevel << std::endl <<
			"blendMode       :" << blendMode << std::endl <<
			"opacity         :" << opacity << std::endl <<
			"name            :" << name.toString() << std::endl;
	}
	AseCelChunk::AseCelChunk(std::ifstream& s)
	{
	}
	bool AseCelChunk::read(std::ifstream& s)
	{
		return false;
	}
	void AseCelChunk::print()
	{
	}
}



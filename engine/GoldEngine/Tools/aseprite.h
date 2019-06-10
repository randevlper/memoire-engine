#pragma once
#include <cstdint>
#include <iosfwd>
#include <vector>
#include <variant>
#include <string>

namespace Aseprite {
	

	static bool tinf_initialized = false;

	using BYTE = uint8_t;
	using WORD = uint16_t;
	using SHORT = int16_t;
	using DWORD = uint32_t;
	using LONG = int32_t;
	using FIXED = int32_t; // convert 16.16 fixed to double: x / 65536

	const int BYTE_MAX = UINT8_MAX;

	struct STRING {
		WORD length;
		std::vector<BYTE> characters;

		bool read(std::ifstream& s);
		std::string toString();
	};

	struct COLOR
	{
		BYTE r;
		BYTE g; 
		BYTE b;
		BYTE a = 255;
	};

	union PIXEL_DATA
	{
		BYTE RGBA[4];
		BYTE Grayscale[2];
		BYTE Indexed[1];
	};

	enum PixelType {
		RGBA, Grayscale, Indexed
	};

	enum AseChunkType {
		PALETTE_OLD_0x0004 = 0x0004,
		PALETTE_OLD_0x0011 = 0x0011,
		LAYER_0x2004 = 0x2004,
		CEL_0x2005 = 0x2005,
		CEL_EXTRA_0x2006 = 0x2006,
		MASK_0x2016 = 0x2016, // 0x2016 DEPRECATED
		PATH_0x2017 = 0x2017, // 0x2017 never used
		FRAME_TAGS_0x2018 = 0x2018,
		PALETTE_0x2019 = 0x2019,
		USER_DATA_0x2020 = 0x2020, //TODO
		SLICE_0x2022 = 0x2022,
	};


	struct AsePaletteOldChunkPacket {
		BYTE numPalletesToSkip;
		BYTE colorsCount;
		COLOR colors[BYTE_MAX + 1];
	};

	struct AsePaletteOldChunk
	{
		WORD numPackets;
		std::vector<AsePaletteOldChunkPacket> packets;

		AsePaletteOldChunk(std::ifstream& s);
		bool read(std::ifstream& s);
		void print();
	};

	struct AseLayerChunk
	{
		WORD flags; // 1 = Visible
				// 2 = Editable
				// 4 = Lock movement
				// 8 = Background
				// 16 = Prefer linked cels
				// 32 = The layer group should be displayed collapsed
				// 64 = The layer is a reference layer
		WORD layerType; //0 - normal, 1 - group layer
		WORD layerChildLevel; // see NOTE.1
		WORD width; // default layer width in pixels . ignored
		WORD height; //ignored
		WORD blendMode; // Normal         = 0
						// Multiply       = 1
						// Screen         = 2
						// Overlay        = 3
						// Darken         = 4
						// Lighten        = 5
						// Color Dodge    = 6
						// Color Burn     = 7
						// Hard Light     = 8
						// Soft Light     = 9
						// Difference     = 10
						// Exclusion      = 11
						// Hue            = 12
						// Saturation     = 13
						// Color          = 14
						// Luminosity     = 15
						// Addition       = 16
						// Subtract       = 17
						// Divide         = 18
		BYTE opacity; //valid only if file header flags field has bit 1 set
		BYTE unused[3];
		STRING name;


		AseLayerChunk(std::ifstream& s);
		bool read(std::ifstream& s);
		void print();
	};

	struct AseCelChunk
	{
		WORD layerIndex; //see NOTE.2
		SHORT x;
		SHORT y;
		BYTE opacity;
		WORD type; //0 raw cel, 1 linked cel, 2 compressed
		BYTE future[7];
		WORD width; //Cel type = 0, 2;
		WORD height; //Cel type = 0, 2;
		std::vector<PIXEL_DATA> pixels;//Cel type 0, 2;
		WORD framePosToLink;//Cel type = 1;
		//std::vector<BYTE> pixelsCompressed;//Cel type 2;

		AseCelChunk(std::ifstream& s, PixelType pixelFormat, DWORD dataSize);
		bool read(std::ifstream& s, PixelType pixelFormat, DWORD dataSize);
		bool readRawPixels(std::ifstream& s, PixelType pixelFormat);
		bool readCompressedPixels(std::ifstream& s, PixelType pixelFormat, DWORD sourceLength);
		void print();
	};

	struct AsePaletteChunkEntry {
		WORD entryFlags;
		COLOR color;
		STRING colorName;
	};

	struct AsePaletteChunk
	{
		DWORD paletteSize; //New palette size(total number of entries)
		DWORD firstColor; //First color index to change
		DWORD lastColor; //Last color index to change
		BYTE future[8]; //for future
		std::vector<AsePaletteChunkEntry> paletteEntries;

		AsePaletteChunk(std::ifstream& s);
		bool read(std::ifstream& s);
		void print();
	};

	struct AseChunk
	{
		// all variants must have move constructor, move assignment operator
		// first variant must have default constructor
		using chunkType = std::variant<
			AsePaletteOldChunk,
			AsePaletteChunk,
			AseLayerChunk,
			AseCelChunk
		>;

		chunkType data;
		WORD type;

		AseChunk(chunkType&& data, WORD type);
	};

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
		void print();
	};

	template<typename OutData>
	bool getHeadPart(std::ifstream& stream, OutData& data) {
		stream.read((char*)& data, sizeof(OutData));
		return stream.good();
	}
	
	class AsepriteFile
	{
	public:
		AseHeader header;
		std::vector<AseFrame> frames;

		AsepriteFile(char filename[]);
		~AsepriteFile();
	};
}
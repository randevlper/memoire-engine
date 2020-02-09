#include "FontLoader.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Font.h"

#define STB_TRUETYPE_IMPLEMENTATION 
#include <stb_truetype.h> /* http://nothings.org/stb/stb_truetype.h */

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" /* http://nothings.org/stb/stb_image_write.h */

FontLoader::FontLoader()
{
}

FontLoader::~FontLoader()
{
}

Font* FontLoader::Load(char* path)
{

	// --- Turn into function
	long size;
	unsigned char* fontBuffer;

	FILE* fontfile = fopen(path, "rb");
	fseek(fontfile, 0, SEEK_END);
	size = ftell(fontfile); //How long
	fseek(fontfile, 0, SEEK_SET);

	fontBuffer =  (unsigned char *)malloc(size);

	if (fontBuffer != nullptr) {
		fread(fontBuffer, size, 1, fontfile);
	}
	
	fclose(fontfile);

	std::cout << "File is " << size << " bytes large." << std::endl;
	// ---

		/* prepare font */
	stbtt_fontinfo info;
	if (!stbtt_InitFont(&info, fontBuffer, 0))
	{
		printf("failed\n");
	}


	//Output parems, For font renderer these will need to be provided
	int b_w = 2048; /* bitmap width */
	int b_h = 128; /* bitmap height */
	int l_h = 128; /* line height */


	/* create a bitmap for the phrase */
	unsigned char* bitmap = (unsigned char *)malloc(b_w * b_h);

	/* calculate font scaling */
	float scale = stbtt_ScaleForPixelHeight(&info, l_h);

	char* word = "I'm going to Mc&FreaKIng~ Lo)S+IT";


	// --  Rendering
	int x = 0;

	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);

	ascent *= scale;
	descent *= scale;

	int i;
	for (i = 0; i < strlen(word); ++i)
	{
		/* how wide is this character */
		int ax;
		int lsb;
		stbtt_GetCodepointHMetrics(&info, word[i], &ax, &lsb);

		/* get bounding box for character (may be offset to account for chars that dip above or below the line */
		int c_x1, c_y1, c_x2, c_y2;
		stbtt_GetCodepointBitmapBox(&info, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

		/* compute y (different characters have different heights */
		int y = ascent + c_y1;

		/* render character (stride and offset is important here) */
		int byteOffset = x + (lsb * scale) + (y * b_w);
		stbtt_MakeCodepointBitmap(&info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

		/* advance x */
		x += ax * scale;

		/* add kerning */
		int kern;
		kern = stbtt_GetCodepointKernAdvance(&info, word[i], word[i + 1]);
		x += kern * scale;
	}

	/* save out a 1 channel image */
	char* file = "out.png";
	stbi_write_png(file, b_w, b_h, 1, bitmap, b_w);

	free(fontBuffer);
	free(fontfile);

	return nullptr;
}

#pragma once
#include <variant>

namespace Aseprite {
	enum AseChunkType {
		PALETTE_OLD_0x0004 = 0x0004,
		PALETTE_OLD_0x0011 = 0x0011,
        LAYER_0x2004	   = 0x2004,
        CEL_0x2005		   = 0x2005,
        CEL_EXTRA_0x2006   = 0x2006,
        MASK_0x2016		   = 0x2016, // 0x2016 DEPRECATED
        PATH_0x2017		   = 0x2017, // 0x2017 never used
        FRAME_TAGS_0x2018  = 0x2018,
        PALETTE_0x2019     = 0x2019,
        USER_DATA_0x2020   = 0x2020, //TODO
        SLICE_0x2022	   = 0x2022,
	};

	struct AsePaletteOldChunk
	{

	};

	struct AseLayerChunk
	{

	};

	struct AseChunk
	{



	};


}
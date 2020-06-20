#include "IndexTypes.h"
#include "VertexTypes.h"

namespace me {
	namespace data {
		static bool posUVVertIBHinit = false;
		bgfx::IndexBufferHandle posUVVertIBH;

		bgfx::IndexBufferHandle getPosUVVertIndexBufferHandle()
		{
			if (!posUVVertIBHinit) {
				posUVVertIBH = bgfx::createIndexBuffer(
					bgfx::makeRef(me::data::PositionUVVertex::indices, 
						sizeof(me::data::PositionUVVertex::verts)));
				posUVVertIBHinit = true;
			}
			return posUVVertIBH;
		}
	}
}
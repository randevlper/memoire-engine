#pragma once
#include "Engine/Nodes/Node.h"
#include "bgfx/bgfx.h"
class Font;

struct TextVertex
{
	float x;
	float y;
	float z;
	uint32_t abgr;
	int16_t m_u;
	int16_t m_v;
	static bgfx::VertexLayout pcvLayout;
	static TextVertex planeVerts[];
	static const uint16_t planeTriList[];
	static void init();
};

class TextRenderer : public Node
{
public:
	TextRenderer();
	~TextRenderer();

	void setFont(Font* font);
	void setText(char* text);
	void render();

private:
	char* _text;
	Font* _font;
	bgfx::TextureHandle textureHandle;
	unsigned int width;
	unsigned int height;

	TextVertex newVerts[4];
	bgfx::VertexBufferHandle vbh;
	bgfx::IndexBufferHandle ibh;
	bgfx::UniformHandle s_font;
	static bgfx::ProgramHandle s_program;
	static bool init;
};
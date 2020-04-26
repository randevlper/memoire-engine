#pragma once
#include <vector>
#include "Engine/Nodes/Node2D.h"
#include "bgfx/bgfx.h"

#include "Engine/Data/VertexTypes.h"

class Font;
class Shader;

class TextRenderer : public Node2D
{
public:
	TextRenderer();
	~TextRenderer() override;

	void setFont(Font* font);
	void setText(char* text);
	void render();
	static void destroy();

private:
	char* _text;
	Font* _font;
	bgfx::TextureHandle textureHandle;
	unsigned int width;
	unsigned int height;
	int scale;

	std::vector<bgfx::VertexBufferHandle> _vbs;
	bgfx::IndexBufferHandle ibh;
	bgfx::UniformHandle s_font;

	void buildVertexBuffers();
	void clearVertexBuffers();

	static Shader* _shader;
	static bool init;
};
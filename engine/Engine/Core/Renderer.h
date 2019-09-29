#pragma once
#include "glm/fwd.hpp"
#include "SDL_stdinc.h"
#include "glm/vec4.hpp"
#include <vector>

struct SpriteData;
struct SDL_Color;
struct SDL_Rect;
struct SDL_Point;
struct AseSprite;
struct AseFrame;
class Timer;

#define PPU 32.0f

namespace bgfx {
	struct DynamicVertexBufferHandle;
	struct TransientVertexBuffer;
	struct IndexBufferHandle;
	struct VertexLayout;
	struct VertexLayoutHandle;
	struct ProgramHandle;
}

struct LineVertex
{
	float x;
	float y;
	float z;
	unsigned int abgr;
	static bgfx::VertexLayout layout;
	static bgfx::VertexLayoutHandle handle;
	static void init();
};

class Renderer
{
public:
	static void init();
	static void quit();
	static void tick();
	//Draw Line 
	static void renderLine(glm::vec2 a, glm::vec2 b, glm::vec4& color = glm::vec4{255, 0, 0, 255}, float width = 0.01f);
	static void renderLines(glm::vec2* points, int pointsCount, glm::vec4& color);

	//Draw Square
	static void renderSquare(SDL_Rect& rect, SDL_Color& color);

	//Draw Circle
	//static void renderCircle(glm::vec2& pos, float& radius);

	static void renderAseFrame(int x, int y, AseFrame* frame);
	static void renderAseSprite(int x, int y, AseSprite* ase);

	static void renderSprite(glm::vec2& pos, SpriteData* spriteData);
	static void renderSprite(int x, int y, SpriteData* spriteData);
	static void clearRenderer(SDL_Color& color);
	static void clearRenderer(int r, int g, int b, int a);
	static void render();

	static void setCameraPos(int x, int y);
	static glm::vec2 getCameraPos();

	static unsigned int colorToHex(glm::vec4& color);
private:
	static glm::vec2* _cameraPos;
	static Renderer* _instance;
	static Timer _fpsTimer;
	static Timer _capTimer;
	static Uint64 _frameCount;
	static bgfx::DynamicVertexBufferHandle lineVerts;
	static bgfx::IndexBufferHandle lineIndicies;
	static bgfx::ProgramHandle lineProgram;
	static const unsigned short planeIndexList[];
	static std::vector<bgfx::TransientVertexBuffer> _tvbs;
	//static LineVertex verts[];
};
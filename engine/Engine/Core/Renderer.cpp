#include "Engine/Core/Renderer.h"

#include <string>

#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "SDL.h"
#include "bgfx/bgfx.h"
#include "bx/bx.h"
#include "bx/math.h"
#include "Engine/Data/AseData.h"
#include "Engine/Core/Context.h"
#include "Engine/Utilities/Timer.h"
#include "FileUtility.h"
#include "Engine/Utilities/TypeConversion.h"

#include "Engine/Utilities/DebugMemory.h"


glm::vec2* Renderer::_cameraPos = DBG_NEW glm::vec2();
Renderer* Renderer ::_instance = nullptr;
Timer Renderer::_fpsTimer = Timer();
Timer Renderer::_capTimer = Timer();
Uint64 Renderer::_frameCount = 0;
float Renderer::_proj[16] = {};
float Renderer::_view[16] = {};

bgfx::DynamicVertexBufferHandle Renderer::lineVerts;
bgfx::IndexBufferHandle Renderer::lineIndicies;
bgfx::ProgramHandle Renderer::lineProgram;
bgfx::VertexLayout LineVertex::layout;
bgfx::VertexLayoutHandle LineVertex::handle;
std::vector<bgfx::TransientVertexBuffer> Renderer::_tvbs;

const unsigned short Renderer::planeIndexList[] = {
	0,1,2,
	0,2,3
};

void LineVertex::init()
{
	layout.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();
	handle = bgfx::createVertexLayout(layout);
}

void Renderer::init()
{
	if (_instance == nullptr) {
		_instance = DBG_NEW Renderer();
		_fpsTimer.start();
		LineVertex::init();
		lineVerts = bgfx::createDynamicVertexBuffer(4, LineVertex::layout, BGFX_BUFFER_ALLOW_RESIZE);
		lineIndicies = bgfx::createIndexBuffer(bgfx::makeRef(&planeIndexList, sizeof(planeIndexList)));
		lineProgram = FileUtility::loadProgram("assets/shaders/vs_line.bin", "assets/shaders/fs_line.bin");
	}
}

void Renderer::quit()
{
	if (_instance != nullptr) {
		bgfx::destroy(lineVerts);
		bgfx::destroy(lineIndicies);
		bgfx::destroy(lineProgram);
		_fpsTimer.stop();
		delete(_instance);
		delete(_cameraPos);
		bgfx::shutdown();
	}
}

void Renderer::tick()
{
	_capTimer.start();
}

void Renderer::renderLine(glm::vec2 a, glm::vec2 b, glm::vec4& color, float width)
{
	//SDL_SetRenderDrawColor(Context::getRenderer(), color.r, color.g, color.b, color.a);
//SDL_RenderDrawLine(Context::getRenderer(), a.x - _cameraPos->x, a.y - _cameraPos->y, b.x - _cameraPos->x, b.y - _cameraPos->y);

	glm::vec2 dir = glm::normalize(b - a) * width;
	glm::vec2 right = glm::rotate(dir, glm::radians(-90.0f));
	glm::vec2 left = glm::rotate(dir, glm::radians(90.0f));
	//Get Verts
	glm::vec2 ar = (a + right);
	glm::vec2 br = (b + right);
	glm::vec2 bl = (b + left);
	glm::vec2 al = (a + left);

	//verts[0] = {ar.x,ar.y, 0.f, 0xff0000ff };
	//verts[1] = { br.x, br.y, 0.f, 0xff0000ff };
	//verts[2] = { bl.x, bl.y, 0.f, 0xff0000ff };
	//verts[3] = { al.x, al.y, 0.f, 0xff0000ff };

	//SDL_Log("Help, %f", verts[0].x);

	bgfx::TransientVertexBuffer tvb;
	bgfx::allocTransientVertexBuffer(&tvb, 4, LineVertex::layout);
	LineVertex* lineData = (LineVertex*)tvb.data;
	lineData[0] = LineVertex{ ar.x, ar.y, 0, Utility::colorToHex(color) };
	lineData[1] = LineVertex{ br.x, br.y, 0, Utility::colorToHex(color) };
	lineData[2] = LineVertex{ bl.x, bl.y, 0, Utility::colorToHex(color) };
	lineData[3] = LineVertex{ al.x, al.y, 0, Utility::colorToHex(color) };
	_tvbs.push_back(tvb);
}

void Renderer::renderLines(glm::vec2* points, int pointsCount, glm::vec4& color)
{
	for (size_t i = 0; i < pointsCount; i++)
	{
		renderLine(points[i], points[(i + 1) % pointsCount], color);
	}
	
	//SDL_SetRenderDrawColor(Context::getRenderer(), color.r, color.g, color.b, color.a);
	//SDL_RenderDrawLines(Context::getRenderer(), points, pointsCount);
}

void Renderer::renderSquare(SDL_Rect& rect, SDL_Color& color)
{
	rect.x -= _cameraPos->x;
	rect.y -= _cameraPos->y;
	//SDL_SetRenderDrawColor(Context::getRenderer(), color.r, color.g, color.b, color.a);
	//SDL_RenderFillRect(Context::getRenderer(), &rect);
}

void Renderer::renderAseFrame(int x, int y, AseFrame* frame)
{
	for (size_t i = 0; i < frame->sprites.size(); i++)
	{
		renderAseSprite(x, y, &frame->sprites[i]);
	}
}

void Renderer::renderAseSprite(int x, int y, AseSprite* ase)
{
	SDL_Rect renderQuad = {(x + ase->xPos)  - _cameraPos->x, (y + ase->yPos) - _cameraPos->y, ase->width, ase->height };
	//SDL_SetRenderDrawColor(Context::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderCopy(Context::getRenderer(), ase->texture, nullptr, &renderQuad);
}

void Renderer::render()
{
	//bgfx::update(lineVerts, 0, bgfx::makeRef( verts.data(), verts.size() * sizeof(LineVertex)));
	//bgfx::update(lineIndicies, 0, bgfx::makeRef(indexes.data(), indexes.size() * sizeof(int)));

	for (size_t i = 0; i < _tvbs.size(); i++)
	{
		bgfx::setVertexBuffer(0, &_tvbs[i], 0, 4);
		bgfx::setIndexBuffer(lineIndicies);
		bgfx::submit(0, lineProgram);
	}

	bx::Vec3 at = { _cameraPos->x, _cameraPos->y,  0.0f };
	bx::Vec3 eye = { _cameraPos->x, _cameraPos->y, -10.0f };
	bx::mtxLookAt(_view, eye, at);
	float left = -float(Context::getWindowWidth()) / 2;
	float right = float(Context::getWindowWidth()) / 2;
	float bottom = -float(Context::getWindowHeight()) / 2;
	float top = float(Context::getWindowHeight()) / 2;

	bx::mtxOrtho(_proj, left, right, bottom, top, 0.1f, 100.0f, 0, bgfx::getCaps()->homogeneousDepth);
	//glm::mat4 projection = glm::ortho(), )
	bgfx::setViewTransform(0, _view, _proj);
	//bx:mtxOrtho(proj, -size * aspectRatio, size * aspectRatio, -size, size)

	//SDL_Log("FPS: %f", _frameCount / ( _fpsTimer.getTicks() / 1000.f));

	std::string title = Context::getWindowTitle();
	title += " FPS: ";
	title += std::to_string((int)(_frameCount / (_fpsTimer.getTicks() / 1000.f)));
	Context::setWindowTitle(title.data());

	const bgfx::Stats* stats = bgfx::getStats();
	bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
		, stats->width
		, stats->height
		, stats->textWidth
		, stats->textHeight
	);

	bgfx::frame();

	//SDL_RenderPresent(Context::getRenderer());
	_frameCount++;

	//if frame finished early
	Uint32 frameTicks = _capTimer.getTicks();
	if (frameTicks < (1000 / Context::getMaxFps())) {
		SDL_Delay((1000 / Context::getMaxFps()) - frameTicks);
	}
	_tvbs.clear();
}

void Renderer::setCameraPos(int x, int y)
{
	_cameraPos->x = x; //- (Context::getWindowWidth()/2);
	_cameraPos->y = y; //- (Context::getWindowHeight()/2);
}

glm::vec2 Renderer::getCameraPos()
{
	return *_cameraPos;
}

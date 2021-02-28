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
#include "Engine/Nodes/Camera.h"

#include "Engine/Utilities/Debug.h"

#include "Engine/Utilities/DebugMemory.h"

#include "Engine/Data/VertexTypes.h"
#include "Engine/AssetManagement/AssetManager.h"

Renderer* Renderer ::_instance = nullptr;
Timer Renderer::_fpsTimer = Timer();
Timer Renderer::_capTimer = Timer();
Uint64 Renderer::_frameCount = 0;
Camera* Renderer::_camera = nullptr;

bgfx::FrameBufferHandle Renderer::_renderFrameBuffer;
bgfx::ProgramHandle Renderer::_scaleProgram;
bgfx::UniformHandle Renderer::_scaleSpriteUniform;
bgfx::IndexBufferHandle Renderer::_scaleIndexBuffer;


bgfx::DynamicVertexBufferHandle Renderer::lineVerts;
bgfx::IndexBufferHandle Renderer::lineIndicies;
bgfx::ProgramHandle Renderer::lineProgram;
std::vector<bgfx::TransientVertexBuffer> Renderer::_tvbs;


void Renderer::init()
{
	if (_instance == nullptr) {
		_instance = DBG_NEW Renderer();
		_fpsTimer.start();
		me::data::PositionColorVertex::init();
		lineVerts = bgfx::createDynamicVertexBuffer(4, me::data::PositionColorVertex::layout, BGFX_BUFFER_ALLOW_RESIZE);
		lineIndicies = bgfx::createIndexBuffer(bgfx::makeRef(&me::data::PositionColorVertex::indices, sizeof(me::data::PositionColorVertex::indices)));
		lineProgram = FileUtility::loadProgram("assets/shaders/vs_line.bin", "assets/shaders/fs_line.bin");
		
		me::data::PositionUVVertex::init();
		_scaleProgram = FileUtility::loadProgram("assets/shaders/vs_scale.bin", "assets/shaders/fs_scale.bin");
		_scaleSpriteUniform = bgfx::createUniform("u_sprite", bgfx::UniformType::Sampler);
		_scaleIndexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(&me::data::PositionUVVertex::indices, sizeof(me::data::PositionUVVertex::indices)));

		_renderFrameBuffer = bgfx::createFrameBuffer(Context::getRenderWidth(), Context::getRenderHeight(), bgfx::TextureFormat::BGRA8);
		bgfx::setViewFrameBuffer(0, _renderFrameBuffer);
	}
}

void Renderer::quit()
{
	if (_instance != nullptr) {
		bgfx::destroy(lineVerts);
		bgfx::destroy(lineIndicies);
		bgfx::destroy(lineProgram);
		bgfx::destroy(_renderFrameBuffer);
		_fpsTimer.stop();
		delete(_instance);
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
	bgfx::allocTransientVertexBuffer(&tvb, 4, me::data::PositionColorVertex::layout);
	me::data::PositionColorVertex* lineData = (me::data::PositionColorVertex*)tvb.data;
	lineData[0] = me::data::PositionColorVertex{ ar.x, ar.y, 0, Utility::colorToHex(color) };
	lineData[1] = me::data::PositionColorVertex{ br.x, br.y, 0, Utility::colorToHex(color) };
	lineData[2] = me::data::PositionColorVertex{ bl.x, bl.y, 0, Utility::colorToHex(color) };
	lineData[3] = me::data::PositionColorVertex{ al.x, al.y, 0, Utility::colorToHex(color) };
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
	rect.x -= _camera->transform.getPosition().x;
	rect.y -= _camera->transform.getPosition().y;
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
	SDL_Rect renderQuad = {(x + ase->xPos)  - _camera->transform.getPosition().x, (y + ase->yPos) - _camera->transform.getPosition().y, ase->width, ase->height };
	//SDL_SetRenderDrawColor(Context::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderCopy(Context::getRenderer(), ase->texture, nullptr, &renderQuad);
}

void Renderer::setCamera(Camera* cam)
{
	_camera = cam;
}

Camera* Renderer::getCamera()
{
	return _camera;
}

void Renderer::sumbitPrimitive(bgfx::ProgramHandle program, unsigned int depth, unsigned int flags)
{
	bgfx::submit(0, program, depth, flags);
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
	//glm::mat4 projection = glm::ortho(), )
	if (_camera == nullptr) {
		Debug::Log("[Renderer] Camera has not been set!");
	}
	else {
		bgfx::setViewTransform(0, _camera->getViewMatrix(), _camera->getProjectionMatrix());
	}
	//bx:mtxOrtho(proj, -size * aspectRatio, size * aspectRatio, -size, size)

	//SDL_Log("FPS: %f", _frameCount / ( _fpsTimer.getTicks() / 1000.f));

	std::string title = Context::getWindowTitle();
	title += " FPS: ";
	title += std::to_string((int)(_frameCount / (_fpsTimer.getTicks() / 1000.f)));
	Context::setWindowTitle(title.data());
	
	//Create a plane to put the frame buffer on
	bgfx::TransientVertexBuffer vb;

	bgfx::allocTransientVertexBuffer(&vb, 4, me::data::PositionUVVertex::layout);
	me::data::PositionUVVertex* vertex = (me::data::PositionUVVertex*)vb.data;
	vertex[0] = { -1.0f, -1.0f, 0.0f, 0, 0 };
	vertex[1] = { 1.0f, -1.0f, 0.0f, 0x7fff, 0 };
	vertex[2] = { 1.0f, 1.0f, 0.0f, 0x7fff, 0x7fff };
	vertex[3] = { -1.0f, 1.0f, 0.0f, 0, 0x7fff };


	bgfx::setIndexBuffer(_scaleIndexBuffer);


	bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
	bgfx::setVertexBuffer(0, &vb);
	bgfx::setTexture(0, _scaleSpriteUniform, bgfx::getTexture(_renderFrameBuffer));
	bgfx::submit(1, _scaleProgram);

	bgfx::frame();

	//SDL_RenderPresent(Context::getRenderer());
	_frameCount++;

	//if frame finished early
	//Uint32 frameTicks = _capTimer.getTicks();
	//if (frameTicks < (1000 / Context::getMaxFps())) {
	//	SDL_Delay((1000 / Context::getMaxFps()) - frameTicks);
	//}
	_tvbs.clear();
}

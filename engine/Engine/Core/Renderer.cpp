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
#include "Engine/Data/UniformTypes.h"

#include "Engine/AssetManagement/AssetManager.h"

Renderer* Renderer ::_instance = nullptr;
Timer Renderer::_fpsTimer = Timer();
Timer Renderer::_capTimer = Timer();
Uint64 Renderer::_frameCount = 0;
Camera* Renderer::_camera = nullptr;

bgfx::FrameBufferHandle Renderer::_renderFrameBuffer;
bgfx::UniformHandle Renderer::_renderSpriteUniform;

bgfx::FrameBufferHandle Renderer::_uiFrameBuffer;
bgfx::UniformHandle Renderer::_uiSpriteUniform;


bgfx::ProgramHandle Renderer::_scaleProgram;
bgfx::IndexBufferHandle Renderer::_scaleIndexBuffer;

bgfx::DynamicVertexBufferHandle Renderer::lineVerts;
bgfx::IndexBufferHandle Renderer::lineIndicies;
bgfx::ProgramHandle Renderer::lineProgram;
std::vector<bgfx::TransientVertexBuffer> Renderer::_tvbs;


void Renderer::init()
{
	if (_instance == nullptr) {
		// Enable debug text.
		bgfx::setDebug(BGFX_DEBUG_TEXT);

		_instance = DBG_NEW Renderer();
		_fpsTimer.start();
		me::data::PositionColorVertex::init();
		lineVerts = bgfx::createDynamicVertexBuffer(4, me::data::PositionColorVertex::layout, BGFX_BUFFER_ALLOW_RESIZE);
		lineIndicies = bgfx::createIndexBuffer(bgfx::makeRef(&me::data::PositionColorVertex::indices, sizeof(me::data::PositionColorVertex::indices)));
		lineProgram = FileUtility::loadProgram("assets/shaders/vs_line.bin", "assets/shaders/fs_line.bin");
		
		me::data::PositionUVVertex::init();
		_scaleProgram = FileUtility::loadProgram("assets/shaders/vs_scale.bin", "assets/shaders/fs_scale.bin");
		_renderSpriteUniform = me::data::getSpriteUniform();
		_uiSpriteUniform = bgfx::createUniform("u_sprite1", bgfx::UniformType::Sampler);

		_scaleIndexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(&me::data::PositionUVVertex::indices, sizeof(me::data::PositionUVVertex::indices)));

		_renderFrameBuffer = bgfx::createFrameBuffer(Context::getRenderWidth(), Context::getRenderHeight(), bgfx::TextureFormat::BGRA8);
		_uiFrameBuffer = bgfx::createFrameBuffer(Context::getRenderWidth(), Context::getRenderHeight(), bgfx::TextureFormat::BGRA8);
		resize();
	}
}

void Renderer::quit()
{
	if (_instance != nullptr) {
		bgfx::destroy(lineVerts);
		bgfx::destroy(lineIndicies);
		bgfx::destroy(lineProgram);

		bgfx::destroy(_scaleProgram);
		bgfx::destroy(_scaleIndexBuffer);

		bgfx::destroy(_renderFrameBuffer);
		bgfx::destroy(_uiFrameBuffer);

		me::data::destroyUniforms();

		_fpsTimer.stop();
		delete(_instance);
		bgfx::shutdown();
	}
}

void Renderer::tick()
{
	_capTimer.start();
}

void Renderer::resize()
{
	int renderWidth = Context::getRenderWidth();
	int renderHeight = Context::getRenderHeight();

	int windowWidth = Context::getWindowWidth();
	int windowHeight = Context::getWindowHeight();

	bgfx::reset(windowWidth, windowHeight, BGFX_RESET_VSYNC);

	bgfx::setViewClear(RENDER_FRAME_BUFFER_INDEX, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF);
	bgfx::setViewRect(RENDER_FRAME_BUFFER_INDEX, 0, 0, renderWidth, renderHeight);

	bgfx::setViewClear(UI_FRAME_BUFFER_INDEX, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0);
	bgfx::setViewRect(UI_FRAME_BUFFER_INDEX, 0, 0, renderWidth, renderHeight);

	bgfx::setViewClear(OUTPUT_BUFFER_INDEX, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
	bgfx::setViewRect(OUTPUT_BUFFER_INDEX, 0, 0, windowWidth, windowHeight);

	bgfx::setViewFrameBuffer(RENDER_FRAME_BUFFER_INDEX, _renderFrameBuffer);
	bgfx::setViewFrameBuffer(UI_FRAME_BUFFER_INDEX, _uiFrameBuffer);
	bgfx::setViewMode(RENDER_FRAME_BUFFER_INDEX, bgfx::ViewMode::DepthDescending);
}

void Renderer::renderLine(glm::vec2 a, glm::vec2 b, glm::vec4& color, float width)
{
	glm::vec2 dir = glm::normalize(b - a) * width;
	glm::vec2 right = glm::rotate(dir, glm::radians(-90.0f));
	glm::vec2 left = glm::rotate(dir, glm::radians(90.0f));
	//Get Verts
	glm::vec2 ar = (a + right);
	glm::vec2 br = (b + right);
	glm::vec2 bl = (b + left);
	glm::vec2 al = (a + left);

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
}

void Renderer::renderSquare(SDL_Rect& rect, SDL_Color& color)
{
	rect.x -= _camera->getTransform().getPosition().x;
	rect.y -= _camera->getTransform().getPosition().y;
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
	SDL_Rect renderQuad = {(x + ase->xPos)  - _camera->getTransform().getPosition().x, (y + ase->yPos) - _camera->getTransform().getPosition().y, ase->width, ase->height };
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

	//Should replace this with a FPS counter in IMGUI
	std::string title = Context::getWindowTitle();
	title += " FPS: ";
	title += std::to_string((int)(_frameCount / (_fpsTimer.getTicks() / 1000.f)));
	Context::setWindowTitle(title.data());
	
	//Create a plane to put the frame buffer on
	bgfx::TransientVertexBuffer vb;
	bgfx::TransientVertexBuffer vb2;

	bgfx::allocTransientVertexBuffer(&vb, 4, me::data::PositionUVVertex::layout);

	me::data::PositionUVVertex* vertex = (me::data::PositionUVVertex*)vb.data;
	vertex[0] = { -1.0f, -1.0f, 0.0f, 0, 0 };
	vertex[1] = { 1.0f, -1.0f, 0.0f, 0x7fff, 0 };
	vertex[2] = { 1.0f, 1.0f, 0.0f, 0x7fff, 0x7fff };
	vertex[3] = { -1.0f, 1.0f, 0.0f, 0, 0x7fff };

	bgfx::touch(UI_FRAME_BUFFER_INDEX);
	bgfx::setState(BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_RGB);
	bgfx::setIndexBuffer(_scaleIndexBuffer);
	bgfx::setVertexBuffer(0, &vb);
	bgfx::setTexture(0, _renderSpriteUniform, bgfx::getTexture(_renderFrameBuffer));
	bgfx::setTexture(1, _uiSpriteUniform, bgfx::getTexture(_uiFrameBuffer));
	bgfx::submit(OUTPUT_BUFFER_INDEX, _scaleProgram);
	bgfx::frame();

	//SDL_RenderPresent(Context::getRenderer());
	_frameCount++;

	//if frame finished early, when a windo is minimized, vsync no longer functions and this is used to prevent max CPU usage
	Uint32 frameTicks = _capTimer.getTicks();
	if (frameTicks < (1000 / Context::getMaxFps())) {
		SDL_Delay((1000 / Context::getMaxFps()) - frameTicks);
	}
	_tvbs.clear();
}

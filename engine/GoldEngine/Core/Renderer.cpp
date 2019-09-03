#include "GoldEngine/Core/Renderer.h"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include "SDL.h"
#include "GoldEngine/Data/SpriteData.h"
#include "GoldEngine/Data/AseData.h"
#include "GoldEngine/Core/Context.h"
#include "GoldEngine/Utilities/Timer.h"

glm::vec2* Renderer::_cameraPos = new glm::vec2();
Renderer* Renderer ::_instance = nullptr;
Timer Renderer::_fpsTimer = Timer();
Timer Renderer::_capTimer = Timer();
Uint64 Renderer::_frameCount = 0;

void Renderer::init()
{
	if (_instance == nullptr) {
		_instance = new Renderer();
		_fpsTimer.start();
	}
}

void Renderer::quit()
{
	if (_instance != nullptr) {
		_fpsTimer.stop();
		delete(_instance);
	}
}

void Renderer::tick()
{
	_capTimer.start();
}

void Renderer::renderLines(SDL_Point* points, int pointsCount, SDL_Color& color)
{
	for (size_t i = 0; i < pointsCount; i++)
	{
		points[i].x -= _cameraPos->x;
		points[i].y -= _cameraPos->y;
	}
	SDL_SetRenderDrawColor(Context::getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawLines(Context::getRenderer(), points, pointsCount);
}

void Renderer::renderSquare(SDL_Rect& rect, SDL_Color& color)
{
	rect.x -= _cameraPos->x;
	rect.y -= _cameraPos->y;
	SDL_SetRenderDrawColor(Context::getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(Context::getRenderer(), &rect);
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
	SDL_SetRenderDrawColor(Context::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(Context::getRenderer(), ase->texture, nullptr, &renderQuad);
}

void Renderer::renderSprite(glm::vec2& pos, SpriteData* spriteData)
{
	renderSprite(pos.x, pos.y, spriteData);
}

void Renderer::renderSprite(int x, int y, SpriteData* spriteData)
{
	SDL_Rect renderQuad = { x - _cameraPos->x, y - _cameraPos->y, spriteData->width, spriteData->height };
	SDL_SetRenderDrawColor(Context::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(Context::getRenderer(), spriteData->texture, nullptr, &renderQuad);
}

void Renderer::clearRenderer(SDL_Color& color)
{
	clearRenderer(color.r, color.g, color.b, color.a);
}

void Renderer::clearRenderer(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(Context::getRenderer(), r, g, b, a);
	SDL_RenderClear(Context::getRenderer());
}

void Renderer::render()
{
	//SDL_Log("FPS: %f", _frameCount / ( _fpsTimer.getTicks() / 1000.f));

	char title[80] = {};

	strcpy(title, Context::getWindowTitle());
	strcat(title, "FPS: ");
	//strcat(title, (_frameCount / (_fpsTimer.getTicks() / 1000.f)));
		//+  + (_frameCount / (_fpsTimer.getTicks() / 1000.f));

	Context::setWindowTitle(title);
	SDL_RenderPresent(Context::getRenderer());
	_frameCount++;

	//if frame finished early
	Uint32 frameTicks = _capTimer.getTicks();
	if (frameTicks < (1000 / Context::getMaxFps())) {
		SDL_Delay((1000 / Context::getMaxFps()) - frameTicks);
	}
}

void Renderer::setCameraPos(int x, int y)
{
	_cameraPos->x = x - (Context::getWindowWidth()/2);
	_cameraPos->y = y - (Context::getWindowHeight()/2);
}

glm::vec2 Renderer::getCameraPos()
{
	return *_cameraPos;
}

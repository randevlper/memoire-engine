#include "GoldEngine/Core/Context.h"
#include "SDL.h"
#include <iostream>
#include "GoldEngine/Core/Physics.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

Context* Context::_instance = nullptr;
bool Context::_shouldClose = nullptr;
int Context::_errorCode = 404;
ContextWindowParems Context::_windowParems = {};
SDL_Window* Context::_window = nullptr;
SDL_Renderer* Context::_renderer = nullptr;

uint64_t Context::_timeNow = 0;
uint64_t Context::_timeLast = 0;

Context::Context()
{

}

Context::~Context()
{
}

void Context::init(ContextWindowParems* parems)
{
	if (_instance == nullptr) {
		_instance = DBG_NEW Context();

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			_errorCode = EXIT_FAILURE;
			return;
		}

		//Validate parems then store copy
		_windowParems = *parems;
		if (_windowParems.renderHeight == 0) {
			_windowParems.renderHeight = _windowParems.windowHeight;
		}
		if (_windowParems.renderWidth == 0) {
			_windowParems.renderWidth = _windowParems.windowWidth;
		}

		_window = SDL_CreateWindow(_windowParems.windowName, 100, 100, 
				_windowParems.windowWidth, _windowParems.windowHeight, SDL_WINDOW_SHOWN);
		if (_window == nullptr) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			_errorCode = EXIT_FAILURE;
			return;
		}

		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (_renderer == nullptr) {
			std::cout << "SDL_CreateRenderer Error" << SDL_GetError() << std::endl;
			_errorCode = EXIT_FAILURE;
			return;
		}

		SDL_RenderSetScale(_renderer, _windowParems.windowWidth / _windowParems.renderWidth, _windowParems.windowHeight / _windowParems.renderHeight);
		SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
		_shouldClose = false;
		_errorCode = 0;

		Physics::init();
	}
}

void Context::quit()
{
	Physics::quit();
	delete(_instance);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool Context::getShouldClose()
{
	return _shouldClose;
}

void Context::setShouldClose(bool value)
{
	_shouldClose = value;
}

SDL_Renderer* Context::getRenderer()
{
	return _renderer;
}

//Anything other then 0 means something went wrong
//Proper usage to be used right after a context function
int Context::getErrorCode()
{
	return _errorCode;
}

int Context::getWindowHeight()
{
	return _windowParems.renderHeight;
}

int Context::getWindowWidth()
{
	return _windowParems.renderWidth;
}

void Context::tick()
{
	_timeLast = _timeNow;
	_timeNow = SDL_GetPerformanceCounter();
}

double Context::getDeltaTime()
{
	return (double)((_timeNow - _timeLast) / (double)SDL_GetPerformanceFrequency());
}

#include "GoldEngine/Utilities/Timer.h"
#include "SDL.h"

Timer::Timer() : _startTicks(0), _pauseTicks(0), _isPaused(false), _isStarted(false)
{
}

Timer::~Timer()
{
}

void Timer::start()
{
	_isStarted = true;
	_isPaused = false;
	//Get the current clock time;
	_startTicks = SDL_GetTicks();
	_pauseTicks = 0;
}

void Timer::stop()
{
	_isStarted = false;
	_isPaused = false;
	_startTicks = 0;
	_pauseTicks = 0;

}

void Timer::pause()
{
	if (_isStarted && !_isPaused) {
		_isPaused = false;
		_pauseTicks = SDL_GetTicks() - _startTicks;
		_startTicks = false;
	}
}

void Timer::unpause()
{
	if (getIsPaused()) {
		_isPaused = false;
		_startTicks = SDL_GetTicks() - _pauseTicks;
		_pauseTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	Uint32 time = 0;
	if (_isStarted) {
		if (_isPaused) {
			time = _pauseTicks;
		}
		else {
			time = SDL_GetTicks() - _startTicks;
		}
	}
	return time;
}

bool Timer::getIsStarted()
{
	return _isStarted;
}

bool Timer::getIsPaused()
{
	return _isStarted && _isPaused;
}

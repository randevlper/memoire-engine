#pragma once
#include "SDL_stdinc.h"

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();
	
	bool getIsStarted();
	bool getIsPaused();

private:
	//Clock time when the timer started
	Uint32 _startTicks;

	//Ticks stored while the timer was paused
	Uint32 _pauseTicks;

	//TimerStatus
	bool _isPaused;
	bool _isStarted;

};
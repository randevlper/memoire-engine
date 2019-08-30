#include "Input.h"
#include "SDL_events.h"
#include "SDL.h"
#include "Context.h"
#include <algorithm>

const unsigned char* Input::_source = nullptr;
unsigned char* Input::_currentPoll = nullptr;
unsigned char* Input::_lastPoll = nullptr;
int Input::_numKeys = 0;
SDL_Event Input::_event = SDL_Event();
Input* Input::_instance = nullptr;

bool Input::getKeyDown(int key)
{
	if (_lastPoll == nullptr || _currentPoll == nullptr) { return false; }
	if (key < _numKeys) {
		//SDL_Log("last %d , current %d", _lastPoll[key], _currentPoll[key]);
		if (_lastPoll[key] == 0 && _currentPoll[key] == 1) {
			return true;
		}
	}
	return false;
}

bool Input::getKeyUp(int key)
{
	if (_lastPoll == nullptr || _currentPoll == nullptr) { return false; }
	if (key < _numKeys) {
		if (_lastPoll[key] == 1 && _currentPoll[key] == 0) {
			return true;
		}
	}
	return false;
}

bool Input::getKey(int key)
{
	if (_lastPoll == nullptr || _currentPoll == nullptr) { return false; }
	if (key < _numKeys) {
		if (_lastPoll[key] == 1 && _currentPoll[key] == 1) {
			return true;
		}
	}
	return false;
}

void Input::init()
{
	if (_instance == nullptr) {
		_instance = new Input();
	}
}

void Input::quit()
{
	if (_instance != nullptr) {
		delete(_instance);
	}
}

Input::Input()
{
	_source = SDL_GetKeyboardState(&_numKeys);
	_currentPoll = new unsigned char[_numKeys];
	_lastPoll = new unsigned char[_numKeys];
}

Input::~Input()
{
	delete[](_currentPoll);
	delete[](_lastPoll);
}

void Input::poll()
{
	while (SDL_PollEvent(&_event) != 0)
	{
		if (_event.type == SDL_QUIT) {
			Context::setShouldClose(true);
		}
	}

	std::copy(_currentPoll, _currentPoll + _numKeys, _lastPoll);
	std::copy(_source, _source + _numKeys, _currentPoll);
}

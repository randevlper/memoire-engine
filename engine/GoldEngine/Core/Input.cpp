#include "Input.h"
#include "SDL_events.h"
#include "Context.h"

const unsigned char* Input::_currentPoll = nullptr;
const unsigned char* Input::_lastPoll = nullptr;
int Input::_numKeys = 0;
SDL_Event Input::_event = SDL_Event();

bool Input::getKeyDown(int key)
{
	if (_lastPoll == nullptr || _currentPoll == nullptr) { return false; }
	if (key < _numKeys) {
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

Input::Input()
{
}

Input::~Input()
{
}

void Input::poll()
{
	while (SDL_PollEvent(&_event) != 0)
	{
		if (_event.type == SDL_QUIT) {
			Context::setShouldClose(true);
		}
	}

	_lastPoll = _currentPoll;
	_currentPoll = SDL_GetKeyboardState(&_numKeys);
}

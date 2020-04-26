#include "Input.h"
#include "SDL_events.h"
#include "SDL.h"
#include "Context.h"
#include <algorithm>
#include <glm/glm.hpp>

#include "Engine/Core/Renderer.h"
#include "Engine/Utilities/DebugMemory.h"
#include "Engine/Utilities/Debug.h"

#include "Engine/Nodes/Node.h"
#include "Engine/Data/Transform.h"

const unsigned char* Input::_source = nullptr;
unsigned char* Input::_currentPoll = nullptr;
unsigned char* Input::_lastPoll = nullptr;
int Input::_numKeys = 0;
unsigned char* Input::_lastMousePoll = nullptr;
unsigned char* Input::_currentMousePoll = nullptr;
int Input::_numMouseKeys = 0;
SDL_Event Input::_event = SDL_Event();
Input* Input::_instance = nullptr;

//Supports values 1-3
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

//Supports values 1-3
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

//Supports values 1-3
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

//Supports values 1-3
bool Input::getMouseKeyDown(int key)
{
	if (_lastMousePoll == nullptr || _currentMousePoll == nullptr) { return false; }
	if (key < _numMouseKeys) {
		//SDL_Log("last %d , current %d", _lastPoll[key], _currentPoll[key]);
		if (_lastMousePoll[key] == 0 && _currentMousePoll[key] == 1) {
			return true;
		}
	}
	return false;
}

//Supports values 1-3
bool Input::getMouseKeyUp(int key)
{
	if (_lastMousePoll == nullptr || _currentMousePoll == nullptr) { return false; }
	if (key < _numMouseKeys) {
		if (_lastMousePoll[key] == 1 && _currentMousePoll[key] == 0) {
			return true;
		}
	}
	return false;
}


//Supports values 1-3
bool Input::getMouseKey(int key)
{
	if (_lastMousePoll == nullptr || _currentMousePoll == nullptr) { return false; }
	if (key < _numMouseKeys) {
		if (_lastMousePoll[key] == 1 && _currentMousePoll[key] == 1) {
			return true;
		}
	}
	return false;
}

glm::ivec2 Input::getMousePos()
{
	glm::ivec2 retval;
	SDL_GetMouseState(&retval.x, &retval.y);
	return retval;
}

void Input::init()
{
	if (_instance == nullptr) {
		_instance = DBG_NEW Input();
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
	_currentPoll = DBG_NEW unsigned char[_numKeys];
	_lastPoll = DBG_NEW unsigned char[_numKeys];

	_numMouseKeys = 6;
	_lastMousePoll = DBG_NEW unsigned char[_numMouseKeys];
	_currentMousePoll = DBG_NEW unsigned char[_numMouseKeys];
}

Input::~Input()
{
	delete[](_currentPoll);
	delete[](_lastPoll);
	delete[](_lastMousePoll);
	delete[](_currentMousePoll);
}

void Input::poll()
{
	//Mouse setup
	std::copy(_currentMousePoll, _currentMousePoll + _numMouseKeys, _lastMousePoll);

	while (SDL_PollEvent(&_event) != 0)
	{
		if (_event.type == SDL_QUIT) {
			Context::setShouldClose(true);
		}

		if (_event.type == SDL_MOUSEBUTTONDOWN) {
			_currentMousePoll[_event.button.button] = 1;
			//Debug::Log(" [INPUT] SDL_MOUSEBUTTONDOWN " + std::to_string(_event.button.button));
		}

		if (_event.type == SDL_MOUSEBUTTONUP) {
			_currentMousePoll[_event.button.button] = 0;
			//Debug::Log(" [INPUT] SDL_MOUSEBUTTONUP " + std::to_string(_event.button.button));
		}
	}

	//Poll Keyboard buttons
	std::copy(_currentPoll, _currentPoll + _numKeys, _lastPoll);
	std::copy(_source, _source + _numKeys, _currentPoll);
}

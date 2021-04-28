#pragma once
union SDL_Event;
#include <vector>
#include  "glm/fwd.hpp"


class Input
{
public:
	static bool getKeyDown(int key);
	static bool getKeyUp(int key);
	static bool getKey(int key);

	static bool getMouseKeyDown(int key);
	static bool getMouseKeyUp(int key);
	static bool getMouseKey(int key);

	static glm::vec2 getMouseWheel();
	static glm::vec2 getMouseWheelLast();

	static glm::ivec2 getMousePos();

	static bool getAnyKeyPressed();
	static bool getAnyKeyPressed(unsigned int start, unsigned int end);

	static void init();
	static void quit();
	//Should only be called once per frame
	static void poll();

	static const std::vector<char>& getKeysPressed();
private:
	Input();
	~Input();
	
	static int _numKeys;
	static unsigned char* _lastPoll;
	static unsigned char* _currentPoll;
	static const unsigned char* _source;

	static int _numMouseKeys;
	static unsigned char* _lastMousePoll;
	static unsigned char* _currentMousePoll;

	static glm::vec2 _mouseWheel;
	static glm::vec2 _mouseWheelLast;

	static SDL_Event _event;
	static Input* _instance;

	static bool keyCheck();

	//lastPoll
	//currentPoll
};
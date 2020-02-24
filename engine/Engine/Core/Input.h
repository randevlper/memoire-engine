#pragma once
union SDL_Event;
#include  "glm/fwd.hpp"

enum Mouse
{
	Left = 0,
	Middle = 1,
	Right = 2
};


class Input
{
public:
	static bool getKeyDown(int key);
	static bool getKeyUp(int key);
	static bool getKey(int key);

	static glm::vec2 getMousePos();

	static void init();
	static void quit();
	//Should only be called once per frame
	static void poll();
private:
	Input();
	~Input();
	
	static int _numKeys;
	static unsigned char* _lastPoll;
	static unsigned char* _currentPoll;
	static const unsigned char* _source;

	static SDL_Event _event;
	static Input* _instance;

	//lastPoll
	//currentPoll
};
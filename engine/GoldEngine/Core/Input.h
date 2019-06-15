#pragma once
union SDL_Event;

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

	static void init();
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

	//lastPoll
	//currentPoll
};
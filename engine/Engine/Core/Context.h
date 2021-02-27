#pragma once
#define SDL_MAIN_HANDLED
#include <stdint.h>

//Should contain anything releated to the engine context

struct ContextWindowParems
{
	const char* windowName;
	//Actual window size
	unsigned int renderWidth, renderHeight;
	unsigned int windowWidth, windowHeight;
	//The internal render size
	unsigned int fps;
	int argc;
	char** argv;
};

struct SDL_Window;
struct SDL_SysWMinfo;
//struct SDL_Renderer;

class Context
{
public:
	static void init(ContextWindowParems* parems);
	static void quit();
	static bool getShouldClose();
	static void setShouldClose(bool value);
	//static SDL_Renderer* getRenderer();
	static int getErrorCode(); 
	static int getRenderHeight();
	static int getRenderWidth();
	static SDL_Window* getWindow();
	static unsigned int getMaxFps();
	
	static const char* getWindowTitle();
	static void setWindowTitle(char* value);

	static void tick();
	static double getDeltaTime();

private:
	static uint32_t _timeNow;
	static uint32_t _timeLast;

	static Context* _instance;
	static bool _shouldClose;
	static int _errorCode;
	static ContextWindowParems _windowParems;
	static SDL_Window* _window;
	//static SDL_Renderer* _renderer;

	static SDL_SysWMinfo* _wmInfo;



	Context();
	~Context();
};
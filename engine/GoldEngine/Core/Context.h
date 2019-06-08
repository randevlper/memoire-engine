#pragma once
#define SDL_MAIN_HANDLED

//Should contain anything releated to the engine context

struct ContextWindowParems
{
	char* windowName;
	//Actual window size
	unsigned int windowWidth, windowHeight;
	//The internal render size
	unsigned int renderWidth, renderHeight;
};

struct SDL_Window;
struct SDL_Renderer;

class Context
{
public:
	static void init(ContextWindowParems* parems);
	static void quit();
	static bool getShouldClose();
	static void setShouldClose(bool value);
	static SDL_Renderer* getRenderer();
	static int getErrorCode(); 
	static int getWindowHeight();
	static int getWindowWidth();

private:
	static Context* _instance;
	static bool _shouldClose;
	static int _errorCode;
	static ContextWindowParems _windowParems;
	static SDL_Window* _window;
	static SDL_Renderer* _renderer;
	Context();
	~Context();
};
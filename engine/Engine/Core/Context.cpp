#include "Engine/Core/Context.h"

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_syswm.h>
#include <bgfx/bgfx.h>

#include "Engine/Core/Physics.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/Audio.h"
#include "Engine/Core/LuaManager.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/FileUtility.h"

#include "Engine/AssetManagement/AssetManager.h"

#include "Engine/Utilities/DebugMemory.h"
#include "Engine/Utilities/ObjectFactory.h"

#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/Nodes/TextRenderer.h"

#include "Engine/Tools/imgui_bgfx.h"

#include "Engine/Core/World.h"
#include "Engine/Nodes/Node.h"
#include "Engine/UI/Button.h"
#include "Engine/UI/Text.h"


Context* Context::_instance = nullptr;
bool Context::_shouldClose = nullptr;
int Context::_errorCode = 404;
ContextWindowParems Context::_windowParems = {};
SDL_Window* Context::_window = nullptr;
//SDL_Renderer* Context::_renderer = nullptr;
SDL_SysWMinfo* Context::_wmInfo = nullptr;

uint32_t Context::_timeNow = 0;
uint32_t Context::_timeLast = 0;

Context::Context()
{

}

Context::~Context()
{
}

void Context::init(ContextWindowParems* parems)
{
	if (_instance == nullptr) {
		_instance = DBG_NEW Context();

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			_errorCode = EXIT_FAILURE;
			return;
		}

		//Validate parems then store copy
		_windowParems = *parems;
		//if (_windowParems.windowHeight == 0) {
		//	_windowParems.windowHeight = _windowParems.windowHeight;
		//}
		//if (_windowParems.windowWidth == 0) {
		//	_windowParems.windowWidth = _windowParems.windowWidth;
		//}

		_window = SDL_CreateWindow(_windowParems.windowName, 100, 100, 
				_windowParems.windowWidth, _windowParems.windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (_window == nullptr) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			_errorCode = EXIT_FAILURE;
			return;
		}

		_wmInfo = DBG_NEW SDL_SysWMinfo();
		SDL_VERSION(&_wmInfo->version);
		//SDL_GetWindowWMInfo(_window, _wmInfo);
		

		if (SDL_GetWindowWMInfo(_window, _wmInfo)) { /* the call returns true on success */
/* success */
			const char* subsystem = "an unknown system!";
			switch (_wmInfo->subsystem) {
			case SDL_SYSWM_UNKNOWN:   break;
			case SDL_SYSWM_WINDOWS:   subsystem = "Microsoft Windows(TM)";  break;
			case SDL_SYSWM_X11:       subsystem = "X Window System";        break;
#if SDL_VERSION_ATLEAST(2, 0, 3)
			case SDL_SYSWM_WINRT:     subsystem = "WinRT";                  break;
#endif
			case SDL_SYSWM_DIRECTFB:  subsystem = "DirectFB";               break;
			case SDL_SYSWM_COCOA:     subsystem = "Apple OS X";             break;
			case SDL_SYSWM_UIKIT:     subsystem = "UIKit";                  break;
#if SDL_VERSION_ATLEAST(2, 0, 2)
			case SDL_SYSWM_WAYLAND:   subsystem = "Wayland";                break;
			case SDL_SYSWM_MIR:       subsystem = "Mir";                    break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 4)
			case SDL_SYSWM_ANDROID:   subsystem = "Android";                break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 5)
			case SDL_SYSWM_VIVANTE:   subsystem = "Vivante";                break;
#endif
			}

			SDL_Log("This program is running SDL version %d.%d.%d on %s",
				(int)_wmInfo->version.major,
				(int)_wmInfo->version.minor,
				(int)_wmInfo->version.patch,
				subsystem);
		}
		else {
			/* call failed */
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't get window information: %s", SDL_GetError());
		}

		bgfx::PlatformData pd;
		pd.ndt = NULL;
		pd.nwh = _wmInfo->info.win.window;

		bgfx::Init init;
		init.platformData = pd;
		init.type = bgfx::RendererType::OpenGL;
		init.resolution.height = _windowParems.windowHeight;
		init.resolution.width = _windowParems.windowWidth;
		init.resolution.reset = BGFX_RESET_VSYNC;

		if (!bgfx::init(init)) {
			_errorCode = EXIT_FAILURE;
			return;
		}

		

		// Enable debug text.
		bgfx::setDebug(BGFX_DEBUG_TEXT);

		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
		bgfx::setViewRect(0, 0, 0, _windowParems.renderWidth, _windowParems.renderHeight);

		bgfx::setViewClear(1, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
		bgfx::setViewRect(1, 0, 0, _windowParems.windowWidth, _windowParems.windowHeight);

		Physics::init(parems->argc, parems->argv);
		Input::init();
		Renderer::init();

		me::util::ObjectFactory::init();

		_errorCode = Audio::init();
		if (_errorCode != 0) {
			return;
		}

		LuaManager::init();
		AssetManager::init();
		me::imgui::create();

		//SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
		_shouldClose = false;
		_errorCode = 0;
	}
}

void Context::quit()
{
	me::imgui::destroy();
	Audio::destroy();
	me::WorldManager::unLoadWorld();
	LuaManager::destroy();
	AssetManager::destroy();
	TextRenderer::destroy();
	SpriteRenderer::destroy();
	FileUtility::destroy();
	Physics::quit();
	Input::quit();
	Renderer::quit();
	delete(_instance);
	delete(_wmInfo);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool Context::getShouldClose()
{
	return _shouldClose;
}

void Context::setShouldClose(bool value)
{
	_shouldClose = value;
}

//SDL_Renderer* Context::getRenderer()
//{
//	return _renderer;
//}

//Anything other then 0 means something went wrong
//Proper usage to be used right after a context function
int Context::getErrorCode()
{
	return _errorCode;
}

int Context::getRenderHeight()
{
	return _windowParems.renderHeight;
}

int Context::getRenderWidth()
{
	return _windowParems.renderWidth;
}

void Context::windowResized(unsigned int windowWidth, unsigned int windowHeight)
{
	_windowParems.windowWidth = windowWidth;
	_windowParems.windowHeight = windowHeight;
	bgfx::setViewRect(1, 0, 0, _windowParems.windowWidth, _windowParems.windowHeight);

	World* world = me::WorldManager::getWorld();

	if (world != nullptr) {
		const std::vector<Node*> nodes = world->getNodes();
		for (size_t i = 0; i < nodes.size(); i++)
		{
			Debug::Log("Resize");
			if (nodes[i]->getType() == "Button") {
				me::ui::Button* buttonSelected = dynamic_cast<me::ui::Button*>(nodes[i]);
				buttonSelected->setSize(buttonSelected->getSize());
			}

			if (nodes[i]->getType() == "Text") {
				me::ui::Text* text = dynamic_cast<me::ui::Text*>(nodes[i]);
				text->setText(text->getText());
			}
		}
	}
}

SDL_Window* Context::getWindow()
{
	return _window;
}

unsigned int Context::getMaxFps()
{
	return _windowParems.fps;
}

const char* Context::getWindowTitle()
{
	return _windowParems.windowName;
}

void Context::setWindowTitle(char* value)
{
	SDL_SetWindowTitle(_window, value);
}

void Context::tick()
{
	_timeLast = _timeNow;
	_timeNow = SDL_GetTicks();
	Input::poll();
	Renderer::tick();

	bgfx::dbgTextClear();
	bgfx::touch(0);
}

double Context::getDeltaTime()
{
	return (double)((_timeNow - _timeLast))/1000;
}

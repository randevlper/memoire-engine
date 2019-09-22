#define STB_IMAGE_IMPLEMENTATION 1
#include "stb_image.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_syswm.h"

#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
#include "bimg/bimg.h"
#include "bx/bx.h"
#include "bx/string.h"
#include "bx/allocator.h"
#include <iostream>


#define AC_SCREEN_WIDTH 1280
#define AC_SCREEN_HEIGHT 720

struct PosColorVertex
{
	float x;
	float y;
	float z;
	uint32_t abgr;
};

static PosColorVertex planeVerts[] = {
	{-1.0f, -1.0f, 0.0f, 0xffffffff},
	{1.0f, -1.0f, 0.0f, 0xffffffff},
	{1.0f, 1.0f, 0.0f, 0xffffffff},
	{-1.0f, 1.0f, 0.0f, 0xffffffff}
};

static const uint16_t planeTriList[] = {
	0,1,2,
	1,3,2
};

int main() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	SDL_Window* win = SDL_CreateWindow("test_bgfx", 100, 100, AC_SCREEN_WIDTH, AC_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(win, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;
	//SDL_GetWindowWMInfo(win, &wmInfo);

	if (SDL_GetWindowWMInfo(win, &wmInfo)) { /* the call returns true on success */
  /* success */
		const char* subsystem = "an unknown system!";
		switch (wmInfo.subsystem) {
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
			(int)wmInfo.version.major,
			(int)wmInfo.version.minor,
			(int)wmInfo.version.patch,
			subsystem);
	}
	else {
		/* call failed */
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't get window information: %s", SDL_GetError());
	}



	bgfx::PlatformData pd;
	pd.ndt = NULL;
	pd.nwh = wmInfo.info.win.window;
	bgfx::setPlatformData(pd);

	bgfx::Init init;
	//init.platformData = pd;
	init.type = bgfx::RendererType::Count;
	init.resolution.height = AC_SCREEN_HEIGHT;
	init.resolution.width = AC_SCREEN_WIDTH;
	init.resolution.reset = BGFX_RESET_VSYNC;
	bgfx::init(init);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

	// Enable debug text.
	bgfx::setDebug(BGFX_DEBUG_TEXT);

	//bgfx::TextureFormat();

	int x, y, n;
	unsigned char* ayse = stbi_load("assets/ayse.png", &x, &y, &n, 0);
	const bgfx::Memory* ayseMem = bgfx::copy(ayse, (x * y * n));
	stbi_image_free(ayse);
	bgfx::TextureHandle ayseTexture = bgfx::createTexture2D(x, y, false, 1,
		bgfx::TextureFormat::RGBA8,
		BGFX_TEXTURE_NONE | BGFX_SAMPLER_UVW_CLAMP | BGFX_SAMPLER_POINT,
		ayseMem);

	bgfx::VertexLayout pcvLayout;
	pcvLayout.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::makeRef(planeVerts, sizeof(planeVerts)), pcvLayout);
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(planeTriList, sizeof(planeTriList)));

	//bgfx::ShaderHandle vsh = loadShader("vs_cubes.bin");
	//bgfx::ShaderHandle fsh = loadShader("fs_cubes.bin");
	//bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh, true);

	SDL_Event e;
	bool quit = false;
	while (!quit) {

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		bgfx::setViewRect(0, 0, 0, AC_SCREEN_WIDTH, AC_SCREEN_HEIGHT);
		// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
		bgfx::touch(0);

		bgfx::dbgTextClear();
		const bgfx::Stats* stats = bgfx::getStats();
		bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
			, stats->width
			, stats->height
			, stats->textWidth
			, stats->textHeight
		);


		bgfx::frame();
	}

	bgfx::shutdown();
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
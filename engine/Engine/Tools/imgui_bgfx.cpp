#include "imgui_bgfx.h"
#include <common/imgui/imgui.h>
#include "Engine/thirdparty/imgui/imgui_impl_sdl.h"

#include <glm/vec2.hpp>

#include "SDL_events.h"
#include <SDL_mouse.h>
#include <SDL_keycode.h>

#include "Engine/Core/Context.h"
#include "Engine/Core/Input.h"

namespace me {
	namespace imgui {
		static float scroll = 0;
		static bool _isOpen = true;

		void create()
		{
			imguiCreate();
			ImGui_ImplSDL2_InitForOpenGL(Context::getWindow(), nullptr);

		}

		void beginFrame()
		{
			glm::vec2 mousePos = Input::getMousePos();
			uint8_t imguiMouse = (Input::getMouseKey(SDL_BUTTON_LEFT) ? IMGUI_MBUT_LEFT : 0) |
				(Input::getMouseKey(SDL_BUTTON_RIGHT) ? IMGUI_MBUT_RIGHT : 0) |
				(Input::getMouseKey(SDL_BUTTON_MIDDLE) ? IMGUI_MBUT_MIDDLE : 0);

			scroll += Input::getMouseWheel().y;

			ImGui_ImplSDL2_NewFrame(Context::getWindow());
			imguiBeginFrame(mousePos.x, mousePos.y, imguiMouse,
				scroll, Context::getWindowWidth(), Context::getWindowHeight());
			//ImGui::ShowDemoWindow();
		}

		void endFrame()
		{
			imguiEndFrame();
		}

		void destroy()
		{
			ImGui_ImplSDL2_Shutdown();
			imguiDestroy();
		}

		bool isAnyWindowFocused()
		{
			return ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow);
		}
		bool isIMGUIOpen()
		{
			return _isOpen;
		}
		void setIMGUIVisibility(bool isOpen)
		{
			_isOpen = isOpen;
		}
	}
}
#include "imgui_bgfx.h"
#include <common/imgui/imgui.h>
#include <glm/vec2.hpp>

#include "SDL_events.h"
#include <SDL_mouse.h>
#include <SDL_keycode.h>

#include "Engine/Core/Context.h"
#include "Engine/Core/Input.h"

float me::imgui::data::scroll = 0;

void me::imgui::create()
{
	imguiCreate();

	ImGuiIO& io = ImGui::GetIO();

	io.KeyMap[ImGuiKey_Tab] = SDL_GetScancodeFromKey(SDLK_TAB);
	io.KeyMap[ImGuiKey_LeftArrow] = SDL_GetScancodeFromKey(SDLK_LEFT);
	io.KeyMap[ImGuiKey_RightArrow] = SDL_GetScancodeFromKey(SDLK_RIGHT);
	io.KeyMap[ImGuiKey_UpArrow] = SDL_GetScancodeFromKey(SDLK_UP);
	io.KeyMap[ImGuiKey_DownArrow] = SDL_GetScancodeFromKey(SDLK_DOWN);
	io.KeyMap[ImGuiKey_Home] = SDL_GetScancodeFromKey(SDLK_HOME);
	io.KeyMap[ImGuiKey_End] = SDL_GetScancodeFromKey(SDLK_END);
	io.KeyMap[ImGuiKey_Delete] = SDL_GetScancodeFromKey(SDLK_DELETE);
	io.KeyMap[ImGuiKey_Backspace] = SDL_GetScancodeFromKey(SDLK_BACKSPACE);
	io.KeyMap[ImGuiKey_Enter] = SDL_GetScancodeFromKey(SDLK_RETURN);
	io.KeyMap[ImGuiKey_Escape] = SDL_GetScancodeFromKey(SDLK_ESCAPE);
	io.KeyMap[ImGuiKey_A] = SDLK_a;
	io.KeyMap[ImGuiKey_C] = SDLK_c;
	io.KeyMap[ImGuiKey_V] = SDLK_v;
	io.KeyMap[ImGuiKey_X] = SDLK_x;
	io.KeyMap[ImGuiKey_Y] = SDLK_y;
	io.KeyMap[ImGuiKey_Z] = SDLK_z;
}

void me::imgui::beginFrame()
{
	glm::vec2 mousePos = Input::getMousePos();
	uint8_t imguiMouse = (Input::getMouseKey(SDL_BUTTON_LEFT) ? IMGUI_MBUT_LEFT : 0) |
		(Input::getMouseKey(SDL_BUTTON_RIGHT) ? IMGUI_MBUT_RIGHT : 0) |
		(Input::getMouseKey(SDL_BUTTON_MIDDLE) ? IMGUI_MBUT_MIDDLE : 0);

	data::scroll += Input::getMouseWheel().y;

	imguiBeginFrame(mousePos.x, mousePos.y, imguiMouse,
		data::scroll, Context::getWindowWidth(), Context::getWindowHeight());
	ImGui::ShowDemoWindow();
}

void me::imgui::endFrame()
{
	imguiEndFrame();
}

void me::imgui::destroy()
{
	imguiDestroy();
}

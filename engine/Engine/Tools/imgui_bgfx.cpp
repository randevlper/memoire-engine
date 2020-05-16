#include "imgui_bgfx.h"
#include <common/imgui/imgui.h>
#include <glm/vec2.hpp>
#include <SDL_mouse.h>

#include "Engine/Core/Context.h"
#include "Engine/Core/Input.h"

void me::imgui::create()
{
	imguiCreate();
}

void me::imgui::beginFrame()
{
	glm::vec2 mousePos = Input::getMousePos();
	uint8_t imguiMouse = (Input::getMouseKey(SDL_BUTTON_LEFT) ? IMGUI_MBUT_LEFT : 0) |
		(Input::getMouseKey(SDL_BUTTON_RIGHT) ? IMGUI_MBUT_RIGHT : 0) |
		(Input::getMouseKey(SDL_BUTTON_MIDDLE) ? IMGUI_MBUT_MIDDLE : 0);

	imguiBeginFrame(mousePos.x, mousePos.y, imguiMouse,
		Input::getMouseWheel().y, Context::getWindowWidth(), Context::getWindowHeight());

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

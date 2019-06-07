#include "GoldEngine/Core/Renderer.h"
#include "GoldEngine/Core/FileUtility.h"
#include "GoldEngine/Core/Context.h"
#include "SDL_render.h"

void Renderer::renderSprite(int x, int y, SpriteData* spriteData)
{
	SDL_Rect renderQuad = { x, y, spriteData->width, spriteData->height };
	SDL_SetRenderDrawColor(Context::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(Context::getRenderer(), spriteData->texture, nullptr, &renderQuad);
}

void Renderer::clearRenderer(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(Context::getRenderer(), r, g, b, a);
	SDL_RenderClear(Context::getRenderer());
}

void Renderer::render()
{
	SDL_RenderPresent(Context::getRenderer());
}

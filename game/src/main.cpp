#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
#endif

#include "GoldEngine/Core/Context.h"
#include "GoldEngine/Core/FileUtility.h"
#include "GoldEngine/Core/Renderer.h"
#include "glm/vec2.hpp"
#include "SDL_events.h"
#include "SDL_pixels.h"
#include "Box2D/Box2D.h"
#include "GoldEngine/Core/Physics.h"
#include "GoldEngine/Data/AseData.h"

#include "GoldEngine/Tools/aseprite.h"


int main(){
	{
		ContextWindowParems cWinParems = { "Ayse why.", 1280, 720, 640, 360 };
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}

		SDL_Color white = { 255,255,255,255 };

		SDL_Event e;
		AseData* aseFile = FileUtility::loadAse("assets/ayse.aseprite");

		b2Body* top = Physics::createBody(glm::vec2( cWinParems.renderWidth/2, 0 ),
			glm::vec2(cWinParems.renderWidth/2,10 ), 0, 1, 0);
		b2Body* bottom = Physics::createBody(glm::vec2(cWinParems.renderWidth / 2, cWinParems.renderHeight),
			glm::vec2(cWinParems.renderWidth / 2, 10), 0, 1, 0);
		b2Body* left = Physics::createBody(glm::vec2(0, cWinParems.renderHeight / 2),
			glm::vec2(10, cWinParems.renderHeight), 0,1);
		b2Body* right = Physics::createBody(glm::vec2(cWinParems.renderWidth, cWinParems.renderHeight / 2),
			glm::vec2(10, cWinParems.renderHeight), 0, 1);


		b2Body* ball = Physics::createBody(glm::vec2(cWinParems.renderWidth / 2, cWinParems.renderHeight / 2 ), 
			glm::vec2(2,2 ), 0, 1, 1);

		//Aseprite::AsepriteFile aseFile();
		
		int frame = 0;
		while (!Context::getShouldClose())
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT) {
					Context::setShouldClose(true);
				}

				if (e.key.keysym.sym == SDLK_0) {
					frame++;
					if (frame >= aseFile->frames.size()) {
						frame = 0;
					}
				}

				if (e.key.keysym.sym == SDLK_w) {
					ball->SetLinearVelocity(ball->GetLinearVelocity() + b2Vec2(0, -1));
				}
				if (e.key.keysym.sym == SDLK_s) {
					ball->SetLinearVelocity(ball->GetLinearVelocity() + b2Vec2(0, 1));
				}
				if (e.key.keysym.sym == SDLK_d) {
					ball->SetLinearVelocity(ball->GetLinearVelocity() + b2Vec2(1, 0));
				}
				if (e.key.keysym.sym == SDLK_a) {
					ball->SetLinearVelocity(ball->GetLinearVelocity() + b2Vec2(-1, 0));
				}
			}

			Physics::tick();
			Renderer::setCameraPos(ball->GetPosition().x, ball->GetPosition().y);

			Renderer::clearRenderer(white);
			Renderer::renderAse(50, 50, aseFile, frame);

			Renderer::renderb2Body(top);
			Renderer::renderb2Body(bottom);
			Renderer::renderb2Body(right);
			Renderer::renderb2Body(left);

			Renderer::renderb2Body(ball);


			Renderer::render();
		}


		FileUtility::unloadAse(aseFile);
		Context::quit();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}
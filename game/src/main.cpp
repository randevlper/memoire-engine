#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
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
#include "GoldEngine/Core/Input.h"


int main(){
	{
		ContextWindowParems cWinParems = { "Ayse why.", 1280, 720, 640, 360 };
		Context::init(&cWinParems);
		Physics::setGravity(glm::vec2(0, 98));
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}

		SDL_Color white = { 255,255,255,255 };

		
		AseData* aseFile = FileUtility::loadAse("assets/ayse.aseprite");

		float groundFriction = 1.0f;

		b2Body* top = Physics::createBody(glm::vec2( cWinParems.renderWidth/2, 0 ),
			glm::vec2(cWinParems.renderWidth/2,10 ), groundFriction, 0.1f);
		b2Body* bottom = Physics::createBody(glm::vec2(cWinParems.renderWidth / 2, cWinParems.renderHeight),
			glm::vec2(cWinParems.renderWidth / 2, 10), groundFriction, 0.1f);
		b2Body* left = Physics::createBody(glm::vec2(0, cWinParems.renderHeight / 2),
			glm::vec2(10, cWinParems.renderHeight), groundFriction,0.1f);
		b2Body* right = Physics::createBody(glm::vec2(cWinParems.renderWidth, cWinParems.renderHeight / 2),
			glm::vec2(10, cWinParems.renderHeight), groundFriction, 0.1f);


		b2Body* ball = Physics::createBody(glm::vec2(cWinParems.renderWidth / 2, cWinParems.renderHeight / 2 ), 
			glm::vec2(2,2 ), 0.5f, 0.1f, 1);
		//ball->SetLinearDamping(5.0f);
		//Aseprite::AsepriteFile aseFile();
		double sum = 0;
		int frame = 0;

		while (!Context::getShouldClose())
		{
			//std::cout << Context::getDeltaTime() << std::endl;
			Context::tick();

			if (Input::getKey(SDL_SCANCODE_D)) {
				ball->SetLinearVelocity(b2Vec2(100, 0));
			}
			if (Input::getKey(SDL_SCANCODE_A)) {
				ball->SetLinearVelocity(b2Vec2(-100, 0));
			}

			b2Vec2 vel = ball->GetLinearVelocity();
			vel.x += (-vel.x * 4.f * Context::getDeltaTime());
			ball->SetLinearVelocity(vel);

			Physics::tick();
			Renderer::setCameraPos(ball->GetPosition().x, ball->GetPosition().y);

			Renderer::clearRenderer(white);

			sum += Context::getDeltaTime();
			double frameLength = (aseFile->frames[frame].frameDuration / 1000);
			if (sum > frameLength) {
				sum = 0;
				frame++;
				if (frame >= aseFile->frames.size()) {
					frame = 0;
				}
			}

			Renderer::renderAseFrame(50, 50, &aseFile->frames[frame]);

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
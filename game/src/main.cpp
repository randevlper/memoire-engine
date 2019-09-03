/*
Memoir Engine
2D Game engine

Editor
	Imgui vs WPF

Engine

Data Oriented
	Generate Data -> Modify -> Renderer

Physics
	SAT Theorm
	Collider, Trigger, Raycast/Linetrace, OverlapShapes
*/

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
#include "GoldEngine/Core/Physics.h"
#include "GoldEngine/Data/AseData.h"
//#include "GoldEngine/Tools/aseprite.h"
#include "GoldEngine/Core/Input.h"


int main(){
	{
		ContextWindowParems cWinParems = { "Ayse why.", 1280, 720, 640, 360, 60 };
		Context::init(&cWinParems);
		Physics::setGravity(glm::vec2(0, 400));
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}

		SDL_Color white = { 255,255,255,255 };

		
		AseData* aseFile = FileUtility::loadAse("assets/ayse.aseprite");

		float groundFriction = 1.0f;

		//Aseprite::AsepriteFile aseFile();
		double sum = 0;
		int frame = 0;

		while (!Context::getShouldClose())
		{
			//std::cout << Context::getDeltaTime() << std::endl;
			Context::tick();

			if (Input::getKey(SDL_SCANCODE_D)) {

			}
			if (Input::getKey(SDL_SCANCODE_A)) {

			}
			if (Input::getKeyDown(SDL_SCANCODE_W)) {

				std::cout << "Down!" << std::endl;
			}
			if (Input::getKeyUp(SDL_SCANCODE_W)) {
				std::cout << "Up!" << std::endl;
			}


			Physics::tick();

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

			Renderer::render();
		}


		FileUtility::unloadAse(aseFile);
		Context::quit();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}
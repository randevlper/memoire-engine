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
#ifdef _DEBUG
	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
#endif

#include "Engine/Core/Context.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/Core/Renderer.h"
#include "glm/vec2.hpp"
#include "SDL_events.h"
#include "SDL_pixels.h"
#include "Engine/Core/Physics.h"
#include "Engine/Data/AseData.h"
//#include "Engine/Tools/aseprite.h"
#include "Engine/Core/Input.h"
#include "Engine/Data/Transform.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Nodes/Node.h"
#include "Engine/Nodes/Collider.h"


int main(){
	{
		ContextWindowParems cWinParems = { "Ayse why.", 1280, 720, 640, 360, 60 };
		Context::init(&cWinParems);
		Physics::setGravity(glm::vec2(0, 400));
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}
		SDL_Color white = { 255,255,255,255 };

		Transform test;
		test.setLocalPosition(glm::vec2(50, 50));
		test.setLocalScale(glm::vec2(10, 10));
		Transform test2;
		test2.setLocalPosition(glm::vec2(50, 50));
		test2.setLocalScale(glm::vec2(2, 2));
		test.setParent(&test2);

		Collider col1;
		col1.transform.setLocalPosition({ 0,100 });

		//Generic File type to inherit from
		AseData* aseFile = FileUtility::loadAse("assets/ayse.aseprite");

		float groundFriction = 1.0f;

		//Aseprite::AsepriteFile aseFile();
		double sum = 0;
		int frame = 0;

		glm::vec2 cameraPos = {0,0};

		while (!Context::getShouldClose())
		{
			//std::cout << Context::getDeltaTime() << std::endl;
			Context::tick();

			if (Input::getKey(SDL_SCANCODE_D)) {
				cameraPos.x += Context::getDeltaTime() * 100;
			}
			if (Input::getKey(SDL_SCANCODE_A)) {
				cameraPos.x -= Context::getDeltaTime() * 100;
			}
			if (Input::getKey(SDL_SCANCODE_W)) {
				//Debug::Log("Up!");
				cameraPos.y -= Context::getDeltaTime() * 100;
			}
			if (Input::getKey(SDL_SCANCODE_S)) {
				//Debug::Log("Up!");
				cameraPos.y += Context::getDeltaTime() * 100;
			}
			Renderer::setCameraPos(cameraPos.x, cameraPos.y);

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
			test2.setLocalAngle(test2.getLocalAngle() + Context::getDeltaTime());
			

			Renderer::renderAseFrame(50, 50, &aseFile->frames[frame]);
			Debug::DrawTransform(&test);
			Debug::DrawTransform(&test2);
			Debug::DrawCollider(&col1);
			Debug::DrawTransform(&col1.transform);
			Renderer::render();
			
		}


		FileUtility::unloadAse(aseFile);
		Context::quit();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}
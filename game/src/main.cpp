/*
Memoir Engine
2D Game engine

Editor
	Imgui

Engine

Data Oriented
	Generate Data -> Modify -> Renderer
*/

#include "Engine/Utilities/DebugMemory.h"

#include <iostream>

#include <bgfx/bgfx.h>
#include <glm/vec2.hpp>
#include <SDL_pixels.h>
#include <SDL_keycode.h>


#include "Engine/Core/Context.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/Physics.h"
#include "Engine/Data/AseData.h"
//#include "Engine/Tools/aseprite.h"
#include "Engine/Core/Input.h"
#include "Engine/Data/Transform.h"
#include "Engine/Utilities/Debug.h"
#include "Engine/Nodes/Node.h"
//#include "Engine/Nodes/Collider.h"
#include "Engine/Nodes/Body.h"
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/Nodes/SpriteRenderer.h"

#include "Engine/AssetManagement/FontLoader.h"
#include "Engine/AssetManagement/Font.h"

#include "Engine/Nodes/TextRenderer.h"
#include "Engine/AssetManagement/AssetManager.h"



int main(int argc, char** argv) {
	{
		ContextWindowParems cWinParems = { "Project-Memoire", 1280, 720, 640, 360, 60 , argc, argv};
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}
		Node test;
		test.transform.setLocalPosition(glm::vec2(20, 20));
		test.transform.setLocalScale(glm::vec2(10, 10));
		Node test2;
		test2.transform.setLocalPosition(glm::vec2(50, 50));
		test.transform.setParent(&test2);

		Body col({});

		//Collider col1;
		//col1.isDebug = true;
		//Collider box;
		//box.transform.translate({ 0,-40 });
		//Physics::addCollider(&box);
		//Collider trigger;
		//trigger.transform.translate({ -40, 0 });
		//trigger.isTrigger = true;
		//Physics::addCollider(&trigger);


		//Physics::addCollider(&col1);
		//Physics::removeCollider(&col1);
		//Physics::addCollider(&col1);
		//Collider col2;
		//col2.isStatic = true;
		//Physics::addCollider(&col2);

		//col1.transform.setLocalPosition({ 0, 0 });
		//col2.transform.setLocalPosition({ 0, 0 });

		//Generic File type to inherit from
		//AseData* aseFile = FileUtility::loadAse("assets/ayse.aseprite");
		//AseData* background = FileUtility::loadAse("assets/background.aseprite");


		float groundFriction = 1.0f;

		//Aseprite::AsepriteFile aseFile();
		//double sum = 0;
		//int frame = 0;

		Transform cameraPos;
		cameraPos.setLocalPosition({ 0,0 });
		//cameraPos.setParent(&col1.transform);

		//SpriteLoader
		Sprite* ayse = FileUtility::loadTexture("assets/ayse.png",
			BGFX_TEXTURE_NONE | BGFX_SAMPLER_POINT, 0, NULL, NULL);
		Sprite* sprite = FileUtility::loadTexture("assets/sprite.png",
			BGFX_TEXTURE_NONE | BGFX_SAMPLER_POINT, 0, NULL, NULL);

		SpriteRenderer* spriteRenderer = DBG_NEW SpriteRenderer();
		spriteRenderer->setSprite(ayse);

		SpriteRenderer* spriteRenderer2 = DBG_NEW SpriteRenderer();
		spriteRenderer2->setSprite(sprite);
		spriteRenderer2->transform.depth = 0.1f;

		spriteRenderer2->transform.setLocalPosition({ -100,-100 });

		AssetManager::init();
		AssetManager::load("assets/fonts/cmunrm.ttf", "64");
		AssetManager::load("assets/fonts/heh.ttf", "64");
		Font* fontTest = AssetManager::get<Font>("assets/fonts/cmunrm.ttf");

		TextRenderer* textRenderer = DBG_NEW TextRenderer();
		textRenderer->setFont(fontTest);
		textRenderer->transform.setLocalScale({ 0.5f,0.5f });
		textRenderer->setText("OHAYOUUUUUU!!!!!");
		textRenderer->setText("YEEHAW");


		Uint32 ticks = 0;
		while (!Context::getShouldClose())
		{
			ticks++;
			Context::tick();

			glm::vec2 movement = glm::vec2();
			if (Input::getKey(SDL_SCANCODE_D)) {
				movement.x = Context::getDeltaTime();
			}
			if (Input::getKey(SDL_SCANCODE_A)) {
				movement.x = -Context::getDeltaTime();
			}
			if (Input::getKey(SDL_SCANCODE_W)) {
				//Debug::Log("Up!");
				movement.y = Context::getDeltaTime();
			}
			if (Input::getKey(SDL_SCANCODE_S)) {
				//Debug::Log("Up!");
				movement.y = -Context::getDeltaTime();
			}
			float speed = 50.0f;
			cameraPos.translate((movement * speed));
			Physics::tick();

			spriteRenderer->transform.setLocalScale({ sin(ticks * Context::getDeltaTime()), 1 });

			//double value = sin(ticks* 0.01);
			//ayse.transform.translate(movement);
			//ayse.transform.setLocalScale({ value * 2, value * 2 });
			//ayse.transform.setLocalAngle(ticks * 0.01);

			//if (Collider::doesCollide(&col1.getWorldGeo(), &col2.getWorldGeo()).penetration > 0) {
			//	Debug::Log("Collide!!");
			//}

			//Need to create animator and animation clips
			//sum += Context::getDeltaTime();
			//double frameLength = (aseFile->frames[frame].frameDuration / 1000);
			//if (sum > frameLength) {
			//	sum = 0;
			//	frame++;
			//	if (frame >= aseFile->frames.size()) {
			//		frame = 0;
			//	}
			//}
			//Renderer::renderLine({ -20,0 }, { 20,0 }, glm::vec4(255,0,0,255));
			//Renderer::renderLine({ 0,20 }, { 0,-20}, glm::vec4(0, 255, 0, 255));
			//Renderer::renderLine({ 20,20 }, { -20,-20 }, glm::vec4(0, 0, 255, 255));
			//Renderer::renderLine({ -20,20 }, { 20,-20 });
			//Renderer::renderLine({ 0,0 }, { -100,-100 });
			//test2.transform.setLocalAngle(test2.transform.getLocalAngle() + Context::getDeltaTime());
			////Mirror option?
			////Renderer::renderAseFrame(-200, -200, &background->frames[0]);
			////Renderer::renderAseFrame(0, -200, &background->frames[0]);
			////Renderer::renderAseFrame(-400, -200, &background->frames[0]);
			//Debug::DrawTransform(&test.transform);
			//Debug::DrawTransform(&test2.transform);
			//bgfx::dbgTextPrintf(0, 4, 0x0f, "Ayse %dW x %dH in pixels", ayse->width, ayse->height);
			//spriteRenderer2->render();
			//spriteRenderer->render();
			textRenderer->render();
			
			Renderer::setCameraPos(cameraPos.getPosition().x,cameraPos.getPosition().y);
			Renderer::render();
			
		}
		delete(textRenderer);
		delete(spriteRenderer);
		delete(spriteRenderer2);
		delete(ayse);
		delete(sprite);
		TextRenderer::destroy();
		SpriteRenderer::destroy();
		FileUtility::destroy();
		AssetManager::destroy();
		Context::quit();
	}
	

	_CrtDumpMemoryLeaks();
	return 0;
}
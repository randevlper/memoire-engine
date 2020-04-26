#include <iostream>
#include <list>
#include <functional>

#include <bgfx/bgfx.h>
#include <glm/vec2.hpp>
#include <SDL_pixels.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>

#include "Engine/Core/Context.h"
#include "Engine/Core/FileUtility.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/World.h"
#include "Engine/Utilities/DebugMemory.h"

//#include "Engine/Tools/aseprite.h"
#include "Engine/Core/Input.h"
#include "Engine/Data/Transform.h"
#include "Engine/Utilities/Debug.h"

#include "Engine/AssetManagement/AssetManager.h"
//Assets should have their own Asset folder for organization
#include "Engine/AssetManagement/Sprite.h"
#include "Engine/AssetManagement/Font.h"
#include "Engine/AssetManagement/AudioClip.h"
#include "Engine/Nodes/SpriteRenderer.h"
#include "Engine/Nodes/TextRenderer.h"
#include "Engine/Nodes/Camera.h"
#include "Engine/Core/Audio.h"
#include "Engine/Nodes/AudioSource.h"

#include "Engine/UI/Button.h"
#include "Engine/UI/Text.h"

AudioSource* audioSource;
me::ui::Text* textTest;

void ohno() {
	audioSource->play();
	textTest->setText("Ays: He was asking for it!\nAne: That was not helpful.\nHe wanted a good time!\nAne: Your idea of a good time is very diffrent from the norm.");
}

int main(int argc, char** argv) {
	{
		ContextWindowParems cWinParems = { "Project-Memoire", 1280, 720, 60 , argc, argv};
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}

		AssetManager::init();

		World* world = DBG_NEW World();


		//Renderer should make a default camera?
		Camera* cam = world->create <Camera>();
		cam->transform.setLocalPosition({ 0,0 });

		Renderer::setCamera(cam);
		
		AssetManager::load("assets/fonts/cmunrm.ttf", "32");
		Font* fontTest = AssetManager::get<Font>("assets/fonts/cmunrm.ttf");
		AssetManager::load("assets/audio/ohno.mp3", "");
		AudioClip* audioTest = AssetManager::get<AudioClip>("assets/audio/ohno.mp3");

		TextRenderer* textRenderer = world->create <TextRenderer>();
		textRenderer->setFont(fontTest);
		textRenderer->transform.setLocalPosition({ -200,0 });
		textRenderer->transform.setLocalScale({ 1,1 });
		textRenderer->setText("OHAYO U U U \nUUU!!!!! A\nThis is a test of the texts\n lol	Test");
		audioSource = world->create<AudioSource>();
		audioSource->setAudioClip(audioTest);


		me::ui::Button* buttonTest = world->create<me::ui::Button>();
		buttonTest->onClick = ohno;
		buttonTest->rectTransform.setPosition({ Context::getWindowWidth() * 0.8f, Context::getWindowHeight() * 0.25f - 50});
		buttonTest->setSize({ Context::getWindowWidth() * 0.2f, 50});


		textTest = world->create<me::ui::Text>();
		textTest->rectTransform.setSize({ Context::getWindowWidth() * 0.8f, Context::getWindowHeight() * 0.25f });
		textTest->setFont(fontTest);
		textTest->setText(
			"Anemone: A fist through the chest does not help someone breathe.\nAys: If they have no lungs they dont need to.\nSte: I wish i was a cat");
		//Callbacks for changing rect properties?

		glm::vec2* textBoxCorners = DBG_NEW glm::vec2[4];
		memcpy(textBoxCorners, textTest->rectTransform.getWindowCorners(), sizeof(glm::vec2) * 4);
		for (size_t i = 0; i < 4; i++)
		{
			textBoxCorners[i].x -= Context::getWindowWidth() / 2;
			textBoxCorners[i].y -= Context::getWindowHeight() / 2;
		}
		
		
		//UI button - Sprites
		//UI Panels - Take code from button and implemnt sprites
		//UI Textbox - text formatting hell
		//Audio looping

		//Scenes Title Screen/Game
		/*
		Title Screen

		Start
		Continue - Store the current state of the game
		Quit
		*/

		while (!Context::getShouldClose())
		{
			Context::tick();
			glm::vec2 mousePos = Input::getMousePos();
			glm::vec2 worldMousePos = cam->screenToWorld(mousePos);

			if(Input::getKeyDown(SDL_SCANCODE_SPACE)) {
				
			}

			textRenderer->render();
			

			buttonTest->sendMouseInfo(mousePos, Input::getMouseKey(SDL_BUTTON_LEFT));
			buttonTest->render();
			textTest->render();

			Renderer::renderLines(textBoxCorners, 4, glm::vec4{ 255,0,0,255 });

			//bgfx::dbgTextPrintf(0, 3, 0x0f, "Camera X: %f Camera Y: %f", cam->transform.getPosition().x, cam->transform.getPosition().y);
			bgfx::dbgTextPrintf(0, 4, 0x0f, "Mouse X: %f Mouse Y: %f", mousePos.x, mousePos.y);

			Renderer::render();
			
		}
		delete(world);
		TextRenderer::destroy();
		SpriteRenderer::destroy();
		FileUtility::destroy();
		AssetManager::destroy();
		Context::quit();
	}
	

	_CrtDumpMemoryLeaks();
	return 0;
}
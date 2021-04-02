#include "Engine/Core/Context.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/WorldManager.h"
#include "Engine/Core/World.h"
#include "Engine/Core/Input.h"
#include "Engine/IMGUI/imgui_bgfx.h"

#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "Engine/Nodes/KinematicBody2D.h"
#include "Engine/Nodes/DynamicBody2D.h"
#include "Engine/Nodes/StaticBody2D.h"

int main(int argc, char** argv) {
	{
		float iExistSoItCompiles = 0.0f; //http://forums.libsdl.org/viewtopic.php?p=47179

		unsigned int renderWidth = 1280;
		unsigned int rednerHeight = 720;
		unsigned int windowWidth = 1280;
		unsigned int windowHeight = 720;

		ContextWindowParems cWinParems = { "Fish", renderWidth, rednerHeight, windowWidth, windowHeight, 60 , argc, argv };
		Context::init(&cWinParems);
		if (Context::getErrorCode() != 0) {
			return Context::getErrorCode();
		}
		me::WorldManager::loadWorld();
		me::WorldManager::postLogic();

		b2Vec2 gravity(0.0f, -10.0f);
		b2World* world = DBG_NEW b2World(gravity);

		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);
		b2Body* groundBody = world->CreateBody(&groundBodyDef);

		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 10.0f);
		groundBody->CreateFixture(&groundBox, 0.0f);

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 4.0f);

		b2Body* body = world->CreateBody(&bodyDef);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		//fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		float timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;

		{
			World* gWorld = me::WorldManager::getWorld();
			if (gWorld != nullptr) {
				gWorld->create<KinematicBody2D>();
				gWorld->create<DynamicBody2D>();
				gWorld->create<StaticBody2D>();
			}
		}
		
		
		while (!Context::getShouldClose())
		{
			Context::tick();
			me::WorldManager::tick();
			me::WorldManager::render();
			Renderer::render();

			world->Step(timeStep, velocityIterations, positionIterations);
			b2Vec2 position = body->GetPosition();
			float angle = body->GetAngle();
			printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
			
			me::WorldManager::postLogic();

			if (me::imgui::isIMGUIOpen()) {
				me::imgui::beginFrame();
				me::imgui::endFrame();
			}
		}
		delete(world);
		Context::quit();
	}
	_CrtDumpMemoryLeaks();
}
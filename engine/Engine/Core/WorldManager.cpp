#include "WorldManager.h"
#include "Engine/Core/World.h"
#include "Engine/Utilities/DebugMemory.h"
#include "Engine/Core/Context.h"


namespace me {
	World* WorldManager::_currentWorld = nullptr;

	void WorldManager::loadWorld()
	{
		unLoadWorld();
		_currentWorld = DBG_NEW World();
	}

	void WorldManager::loadWorld(std::string path)
	{

	}

	void WorldManager::unLoadWorld()
	{
		if (_currentWorld != nullptr) {
			delete(_currentWorld);
		}
	}

	void WorldManager::tick()
	{
		if (_currentWorld != nullptr) {
			_currentWorld->tick(Context::getDeltaTime());
		}
	}

	void WorldManager::render()
	{
		if (_currentWorld != nullptr) {
			_currentWorld->render();
		}
	}

	World* WorldManager::getWorld()
	{
		return _currentWorld;
	}
}



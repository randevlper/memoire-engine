#include "WorldManager.h"
#include "Engine/Core/World.h"
#include "Engine/Utilities/DebugMemory.h"
#include "Engine/Core/Context.h"

#include "Engine/Core/FileUtility.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace me {
	World* WorldManager::_currentWorld = nullptr;

	void WorldManager::loadWorld()
	{
		unLoadWorld();
		_currentWorld = DBG_NEW World();
	}

	void WorldManager::loadWorld(std::string path)
	{
		json file;
		if (FileUtility::loadJson(path.c_str(), file)) {
			//Should use Assetmanager hot reload
			unLoadWorld();
			_currentWorld = DBG_NEW World();
			_currentWorld->from_json(file);
		}
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



#include "WorldManager.h"

#include <sstream>

#include "Engine/Core/World.h"
#include "Engine/Core/LuaManager.h"

#include "Engine/Utilities/DebugMemory.h"
#include "Engine/Core/Context.h"

#include "Engine/Core/FileUtility.h"
#include "Engine/Nodes/Camera.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Utilities/Debug.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace me {
	World* WorldManager::_currentWorld = nullptr;

	//Empty world with only a camera
	void WorldManager::loadWorld()
	{
		unLoadWorld();
		_currentWorld = DBG_NEW World();
		Camera* camera = _currentWorld->create<Camera>();
		camera->setName("Camera");
		Renderer::setCamera(camera);
	}

	//Expects no filetype
	bool WorldManager::loadWorld(std::string path)
	{
		std::ostringstream worldPath;
		worldPath << path;
		worldPath << WORLD_FILE_TYPE;
		json file;
		if (FileUtility::loadJson(worldPath.str().c_str(), file)) {
			//Should use Assetmanager hot reload
			unLoadWorld();
			_currentWorld = DBG_NEW World();
			_currentWorld->from_json(file);

			for each (Node* node in _currentWorld->getNodes())
			{
				if (node->getType() == "Camera") {
					Camera* cam = dynamic_cast<Camera*>(node);
					Renderer::setCamera(cam);
					break;
				}
			}
			//Load lua
			std::ostringstream luaPath;
			luaPath << path;
			luaPath << ".lua";
			std::string lua = FileUtility::loadTextFile(luaPath.str().c_str());
			LuaManager::loadLua(lua.c_str());

			return true;
		} else{
			Debug::LogError("[World] World does not exist! " + path);
			return false;
		}

	}

	void WorldManager::unLoadWorld()
	{
		Renderer::setCamera(nullptr);
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



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
	World* WorldManager::_toLoadWorld = nullptr;
	Camera* WorldManager::_toLoadCamera = nullptr;

	std::string WorldManager::_toLoadWorldPath = "";

	//Empty world with only a camera
	void WorldManager::loadWorld()
	{
		_toLoadWorld = DBG_NEW World();
		Camera* camera = _toLoadWorld->create<Camera>();
		camera->setName("Camera");
		_toLoadCamera = camera;
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
			_toLoadWorld = DBG_NEW World();
			_toLoadWorld->from_json(file);

			for each (Node* node in _toLoadWorld->getNodes())
			{
				if (node->getType() == "Camera") {
					Camera* cam = dynamic_cast<Camera*>(node);
					_toLoadCamera = cam;
					break;
				}
			}

			_toLoadWorldPath = path;

			return true;
		} else{
			Debug::LogError("[World] World does not exist! " + path);
			return false;
		}

	}

	bool WorldManager::postRender()
	{
		if (_currentWorld != nullptr) {
			_currentWorld->postRender();
		}

		if (_toLoadWorld != nullptr) {
			if (_currentWorld != nullptr) {
				LuaManager::luaFunction("destroy");
				unLoadWorld();
			}
			_currentWorld = _toLoadWorld;
			Renderer::setCamera(_toLoadCamera);
			_toLoadWorld = nullptr;
			_toLoadCamera = nullptr;

			LuaManager::destroy();
			LuaManager::init();

			//Load lua
			std::ostringstream luaPath;
			luaPath << _toLoadWorldPath;
			luaPath << ".lua";
			std::string lua = FileUtility::loadTextFile(luaPath.str().c_str());
			LuaManager::loadLua(lua.c_str());
			LuaManager::luaFunction("init");

			_toLoadWorldPath = "";
			return true;
		}
		return false;
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



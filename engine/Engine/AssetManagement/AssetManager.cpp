#include "AssetManager.h"

#include <filesystem>

#include "FontLoader.h"
#include "Engine/Utilities/DebugMemory.h"


std::map<std::string, AssetLoader*> AssetManager::_loaders = std::map<std::string, AssetLoader*>();
std::map<std::string, void*> AssetManager::_assets = std::map<std::string, void*>();

void AssetManager::load(std::string path, std::string vars)
{
	std::filesystem::path p = std::filesystem::path(path);
	if (std::filesystem::exists(path)) {
		Debug::Log("AssetManager: Exists: " + path);

	}
	else {
		Debug::Log("AssetManager: Does Not Exist: " + path);
	}
}

void AssetManager::init() {
	FontLoader* _fontLoader = DBG_NEW FontLoader();
	_fontLoader->init();
	_loaders.insert(std::pair<std::string, AssetLoader*>(_fontLoader->_fileExtension, _fontLoader));
}

void AssetManager::destroy() {
	std::map<std::string, AssetLoader*>::iterator it = _loaders.begin();
	for (std::pair<std::string, AssetLoader*> element : _loaders) {
		element.second->destroy();
		delete(element.second);
	}
}
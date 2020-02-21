#include "AssetManager.h"

#include <filesystem>

#include "FontLoader.h"
#include "AssetLoader.h"

#include "Engine/Utilities/DebugMemory.h"


std::map<std::string, AssetLoader*> AssetManager::_loaders = std::map<std::string, AssetLoader*>();
std::map<std::string, Asset*> AssetManager::_assets = std::map<std::string, Asset*>();

void AssetManager::load(std::string path, std::string vars)
{
	std::filesystem::path p = std::filesystem::path(path);
	if (std::filesystem::exists(path)) {
		Debug::Log("AssetManager: Exists: " + path);
		std::map<std::string, AssetLoader*>::iterator it = _loaders.find(p.extension().string());
		if (it == _loaders.end()) {
			Debug::Log("AssetManager: Loader not found for " + p.extension().string());
		}
		else {
			//TODO Add to assets
			it->second->load(path, vars);
			Debug::Log("AssetManager: Loaded asset at " + path);
		}
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
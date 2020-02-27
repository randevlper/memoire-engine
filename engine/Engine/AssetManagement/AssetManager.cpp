#include "AssetManager.h"

#include <filesystem>
#include <memory>

#include "AssetLoader.h"
#include "FontLoader.h"
#include "SpriteLoader.h"
#include "ShaderLoader.h"

#include "Engine/Utilities/DebugMemory.h"


std::map<std::string, AssetLoader*> AssetManager::_loaders = std::map<std::string, AssetLoader*>();
std::map<std::string, Asset*> AssetManager::_assets = std::map<std::string, Asset*>();
bool AssetManager::isInit = false;

void AssetManager::load(std::string path, std::string vars)
{
	if (!isInit) {
		Debug::Log("AssetManager: Is not init!");
		return;
	}

	std::filesystem::path p = std::filesystem::path(path);
	if (std::filesystem::exists(path)) {
		Debug::Log("AssetManager: Exists: " + path);
		std::map<std::string, AssetLoader*>::iterator it = _loaders.find(p.extension().string());
		if (it == _loaders.end()) {
			Debug::Log("AssetManager: Loader not found for " + p.extension().string());
		}
		else {
			//TODO Add to assets
			Asset* asset = it->second->load(path, vars);
			if (asset != nullptr) {
				_assets.insert(std::pair<std::string, Asset*>(path, asset));
				Debug::Log("AssetManager: Loaded asset at " + path);
			}
			else {
				Debug::Log("AssetManager: Failed to load asset at " + path);
			}
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

	SpriteLoader* _spriteLoader = DBG_NEW SpriteLoader();
	_spriteLoader->init();
	_loaders.insert(std::pair<std::string, AssetLoader*>(_spriteLoader->_fileExtension, _spriteLoader));
	
	ShaderLoader* _shaderLoader = DBG_NEW ShaderLoader();
	_shaderLoader->init();
	_loaders.insert(std::pair<std::string, AssetLoader*>(_shaderLoader->_fileExtension, _shaderLoader));

	isInit = true;

	//Need to make some sort of system for required Assets for the loader to load
	AssetManager::load("assets/shaders/vs_sprite.bin", "assets/shaders/fs_sprite.bin");
}

void AssetManager::destroy() {
	//for (std::pair<std::string, Asset*> element : _assets) {
	//	Debug::Log("Deleting " + element.first);
	//	element.second->destroy();
	//	delete(element.second);
	//}
	if (!isInit) {
		Debug::Log("AssetManager: Is not init!");
	}

	for (auto const& [key, val] : _assets)
	{
		Debug::Log("AssetManager: Destroying: " + key);
		//val->destroy();
		delete(val);
	}
	_assets.clear();

	for (auto const& [key, val] : _loaders)
	{
		val->destroy();
		delete(val);
	}
	_loaders.clear();

	isInit = false;
}
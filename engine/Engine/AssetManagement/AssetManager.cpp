#include "AssetManager.h"

#include <filesystem>
#include <memory>

#include "AssetLoader.h"
#include "FontLoader.h"
#include "SpriteLoader.h"
#include "ShaderLoader.h"
#include "AudioClipLoader.h"
#include "JSONLoader.h"


std::unordered_map<std::string, AssetLoader*> AssetManager::_loaders = std::unordered_map<std::string, AssetLoader*>();
std::unordered_map<std::string, Asset*> AssetManager::_assets = std::unordered_map<std::string, Asset*>();
bool AssetManager::isInit = false;
bool AssetManager::supressNotLoadedWarning = false;

void AssetManager::load(std::string path, std::string vars)
{
	if (!isInit) {
		Debug::LogError("[AssetManager] Is not init!");
		return;
	}

	supressNotLoadedWarning = true;
	if (get<Asset>(path) != nullptr) {
		Debug::Log("[AssetManager] " + path + " Is already loaded!");
		supressNotLoadedWarning = false;
		return;
	}
	supressNotLoadedWarning = false;

	std::filesystem::path p = std::filesystem::path(path);
	if (std::filesystem::exists(path)) {
		//Debug::Log("[AssetManager] Exists: " + path);
		std::unordered_map<std::string, AssetLoader*>::iterator it = _loaders.find(p.extension().string());
		if (it == _loaders.end()) {
			Debug::LogError("[AssetManager] Loader not found for " + p.extension().string());
		}
		else {
			//TODO Add to assets
			Asset* asset = it->second->load(path, vars);
			asset->path = path;
			asset->parems = vars;
			if (asset != nullptr) {
				_assets.insert(std::pair<std::string, Asset*>(path, asset));
				Debug::Log("[AssetManager] Loaded asset at " + path);
			}
			else {
				Debug::LogError("[AssetManager] FAILED to load asset at " + path);
			}
		}
	}
	else {
		Debug::Log("[AssetManager] Does Not Exist: " + path);
	}
	
}

void AssetManager::init() {

	initLoader<FontLoader>();
	initLoader<SpriteLoader>();
	initLoader<ShaderLoader>();
	initLoader<AudioClipLoader>();
	initLoader<JSONLoader>();

	isInit = true;

	//Need to make some sort of system for required Assets for the loader to load
	AssetManager::load("assets/shaders/vs_sprite.bin", "assets/shaders/fs_sprite.bin");
	AssetManager::load("assets/shaders/vs_tile.bin", "assets/shaders/fs_tile.bin");
	AssetManager::load("assets/shaders/vs_ui.bin", "assets/shaders/fs_ui.bin");
	AssetManager::load("assets/shaders/vs_uisprite.bin", "assets/shaders/fs_uisprite.bin");

	AssetManager::load("assets/fonts/cmunrm.ttf", "32");
	AssetManager::load("assets/ui/box.png", "");
}


void AssetManager::destroy() {
	//for (std::pair<std::string, Asset*> element : _assets) {
	//	Debug::Log("Deleting " + element.first);
	//	element.second->destroy();
	//	delete(element.second);
	//}
	if (!isInit) {
		Debug::LogError("[AssetManager] Is not init!");
	}

	for (auto const& [key, val] : _assets)
	{
		Debug::Log("[AssetManager] Destroying: " + key);
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
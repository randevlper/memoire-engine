#pragma once
#include <map>
#include <string>
#include "Engine/Utilities/Debug.h"
#include <nlohmann/json.hpp>

class AssetLoader;
#include "Asset.h"

class AssetManager
{
public:
	static void load(std::string path, std::string vars);
	
	static void init();
	static void destroy();

	template <class T>
	static T* get(std::string name);

	template <class T>
	static T* get_json(nlohmann::json j);

private:
	//Asset, Pointer
	static std::map<std::string, Asset*> _assets;
	//Extension, Pointer
	static std::map<std::string, AssetLoader*> _loaders;

	static bool isInit;
};

template<class T>
inline T* AssetManager::get(std::string name)
{
	static_assert(std::is_base_of<Asset, T>::value, "T not derived from Asset");
	if (!isInit) {
		Debug::Log("AssetManager: Is not init!");
		return nullptr;
	}

	std::map<std::string, Asset*>::iterator it = _assets.find(name);
	if (it == _assets.end())
	{
		Debug::Log(" AssetManager: " + name + " is not loaded!");
		return nullptr;
	}
	
	if (T * retval = dynamic_cast<T*>(it->second)) {
		
		return retval;
	}
	
	Debug::Log("AssetManager: Cast failed!");
	return nullptr;
}

template<class T>
inline T* AssetManager::get_json(nlohmann::json j)
{
	T* retval = get<T>(j["name"]);
	if (retval == nullptr) {
		load(j["name"], j["parems"]);
		retval = get<T>(j["name"]);
	}
	return retval;
}

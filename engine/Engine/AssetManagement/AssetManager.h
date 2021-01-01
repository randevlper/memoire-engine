#pragma once
#include <unordered_map>
#include <string>
#include "Engine/Utilities/Debug.h"
#include <nlohmann/json.hpp>
#include "Engine/Utilities/DebugMemory.h"

class AssetLoader;
#include "Asset.h"

class AssetManager
{
public:
	static void load(std::string path, std::string vars);
	
	static void init();
	static void destroy();

	template<class T>
	static void initLoader();

	template <class T>
	static T* get(std::string name);

	template <class T>
	static T* get_json(nlohmann::json j); 

	template <class T>
	static T* getLoad(std::string path, std::string vars);

private:
	//Asset, Pointer
	static std::unordered_map<std::string, Asset*> _assets;
	//Extension, Pointer
	static std::unordered_map<std::string, AssetLoader*> _loaders;

	static bool isInit;
	static bool supressNotLoadedWarning;
};

template<class T>
inline void AssetManager::initLoader()
{
	static_assert(std::is_base_of<AssetLoader, T>::value, "T not derived from AssetLoader");
	T* _loader = DBG_NEW T();
	_loader->init();
	_loaders.insert(std::pair<std::string, T*>(_loader->_fileExtension, _loader));
}

template<class T>
inline T* AssetManager::get(std::string name)
{
	static_assert(std::is_base_of<Asset, T>::value, "T not derived from Asset");
	if (!isInit) {
		Debug::LogError("[AssetManager] Is not init!");
		return nullptr;
	}

	std::unordered_map<std::string, Asset*>::iterator it = _assets.find(name);
	if (it == _assets.end())
	{
		if(!supressNotLoadedWarning){
			Debug::LogError(" AssetManager: " + name + " is not loaded!");
		}
		return nullptr;
	}
	
	if (T * retval = dynamic_cast<T*>(it->second)) {
		
		return retval;
	}
	
	Debug::LogError("AssetManager: Cast failed!");
	return nullptr;
}

template<class T>
inline T* AssetManager::get_json(nlohmann::json j)
{
	T* retval = get<T>(j["path"]);
	if (retval == nullptr) {
		load(j["path"], j["parems"]);
		retval = get<T>(j["path"]);
	}
	return retval;
}

template<class T>
inline T* AssetManager::getLoad(std::string path, std::string vars) {
	T* retval = get<T>(path);
	if (retval == nullptr) {
		load(path, vars);
		retval = get<T>(path);
	}
	return retval;
}
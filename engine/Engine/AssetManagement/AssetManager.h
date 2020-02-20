#pragma once
#include <map>
#include <string>
#include "Engine/Utilities/Debug.h"

class AssetLoader;

class AssetManager
{
public:
	static void load(std::string path, std::string vars);
	
	static void init();
	static void destroy();

	template <class T>
	static T* get(std::string name);

private:
	//Asset, Pointer
	static std::map<std::string, void*> _assets;
	//Extension, Pointer
	static std::map<std::string, AssetLoader*> _loaders;
};

template<class T>
inline T* AssetManager::get(std::string name)
{
	std::map<std::string, void*>::iterator it = _assets.find(name);
	if (it == _assets.end())
	{
		Debug::Log(" AssetManager: " + name + " is not loaded!");
		return nullptr;
	}
	return (T*)it->second;
}

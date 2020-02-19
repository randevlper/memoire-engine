#pragma once
#include <map>
#include <string>

class AssetManager
{
public:
	static void load(std::string path, std::string vars);
	
	static void init();
	static void destroy();

	template <class T>
	static T* get(std::string name);

private:
	std::map<std::string, void*> assets;

	//Loaders
};

template<class T>
inline T* AssetManager::get(std::string name)
{

	return nullptr;
}

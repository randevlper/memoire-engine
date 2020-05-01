#include "JSONLoader.h"

#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Engine/Utilities/DebugMemory.h"
#include "JSON.h"

JSONLoader::JSONLoader()
{
}

JSONLoader::~JSONLoader()
{
}

void JSONLoader::init()
{
}

void JSONLoader::destroy()
{
}

Asset* JSONLoader::load(std::string path, std::string vars)
{
	std::ifstream file(path);
	if (file.is_open()) {
		json j;
		file >> j;
		return DBG_NEW JSON(j);
	}
	return nullptr;
}

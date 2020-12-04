#include "DialogueLoader.h"
#include "Dialogue.h"
#include <nlohmann/json.hpp>

#include "Engine/Core/FileUtility.h"

#include "Engine/Utilities/DebugMemory.h"

namespace lb {
	DialogueLoader::DialogueLoader()
	{
	}

	DialogueLoader::~DialogueLoader()
	{
	}

	void DialogueLoader::init()
	{
	}

	void DialogueLoader::destroy()
	{
	}

	Asset* DialogueLoader::load(std::string path, std::string vars)
	{
		Dialogue* retval = nullptr;
		nlohmann::json json;
		if (FileUtility::loadJson(path.c_str(), json)) {
			 retval = DBG_NEW Dialogue(json);
		}
		return retval;
	}
}
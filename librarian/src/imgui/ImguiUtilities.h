#pragma once
#include <string>
#include <filesystem>
#include <sstream>
namespace lb {
	namespace imgui {
		namespace utilities {
			std::string selectFile(bool& isOpen, std::filesystem::directory_entry& directory, std::string folder, std::string fileExt);
		}
	}
}

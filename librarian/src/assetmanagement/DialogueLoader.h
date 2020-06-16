#pragma once
#include "Engine/AssetManagement/AssetLoader.h"

namespace lb {
	class DialogueLoader : public AssetLoader
	{
	public:
		DialogueLoader();
		~DialogueLoader();

		void init() override;
		void destroy() override;
		Asset* load(std::string path, std::string vars) override;
		const std::string _fileExtension = ".dialogue";
	private:

	};
}
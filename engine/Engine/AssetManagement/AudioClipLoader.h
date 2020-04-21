#pragma once
#include "AssetLoader.h"

class AudioClipLoader : public AssetLoader
{
public:

	AudioClipLoader();
	~AudioClipLoader();

	void init() override;
	void destroy() override;
	Asset* load(std::string path, std::string vars) override;
	
	//Only support MP3 at the moment
	std::string _fileExtension = ".mp3";

private:
	

};
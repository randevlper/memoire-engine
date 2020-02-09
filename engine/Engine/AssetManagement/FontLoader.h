#pragma once
class Font;

class FontLoader
{
public:
	FontLoader();
	~FontLoader();

	static Font* Load(char* path);

private:

};
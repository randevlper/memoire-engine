#pragma once
class Font;

class FontLoader
{
public:
	static void init();
	static void destroy();
	static Font* load(char* path, int fontSize);

private:

	static void* _FT_LIB;
};
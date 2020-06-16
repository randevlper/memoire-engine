#pragma once
#include "Engine/AssetManagement/Asset.h"

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>
#include <unordered_map>

struct Character
{
	bgfx::TextureHandle Handle;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class Font : public Asset
{
public:
	Font(void* face, unsigned int fontSize);
	~Font() override;

	Character getCharacter(char c);

private:
	void* _ft_face;
	int _fontHeight;
	std::unordered_map<char, Character> characters;
};
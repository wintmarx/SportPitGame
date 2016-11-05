#pragma once
#include "GLHeaders.h"
#include "Texture.h"
#include <iostream>
#include <vector>
#include <string>


class TexturesController
{
public:
	TexturesController();
	~TexturesController();
	uint32_t AddTexture(const char *filePath);
	uint32_t GetTextureWidth(uint32_t textureId);
	uint32_t GetTextureHeight(uint32_t textureId);
private:
	std::vector<Texture*> *textures;
};


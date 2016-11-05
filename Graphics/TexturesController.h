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
private:
	int AddTexture(const char *filePath);
	std::vector<Texture*> *textures;
};


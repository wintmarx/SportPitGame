#pragma once
#include "PNGLoader.h"
#include "TGALoader.h"

class Texture
{
public:
	~Texture();
	Texture(std::vector<uint8_t> *image, const char *filePath, int id);
	bool IsEqualFilePath(const char *filePath);
	int GetId();
private:
	std::vector<uint8_t> *image;
	int id;
	const char *filePath;
};


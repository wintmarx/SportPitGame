#include "Texture.h"



Texture::Texture(std::vector<uint8_t> *image, const char *filePath, uint32_t id, uint32_t width, uint32_t height)
{
	this->filePath = filePath;
	this->id = id;
	this->width = width;
	this->height = height;
	for (int i = 0; i < image->size(); i++)
		this->image->push_back((*image)[i]);
}


Texture::~Texture()
{
	delete image;
	delete[] filePath;
}

bool Texture::IsEqualFilePath(const char *filePath)
{
	return strcmpi(this->filePath, filePath) == 0;
}

int Texture::GetId()
{
	return id;
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}



#include "Texture.h"



Texture::Texture(std::vector<uint8_t> *image, const char *filePath, int id)
{
	this->filePath = filePath;
	this->id = id;
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



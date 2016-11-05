#include "TexturesController.h"



TexturesController::TexturesController()
{
}


TexturesController::~TexturesController()
{
	for (int i = 0; i < textures->size(); i++)
	{
		delete (*textures)[i];
	}
	delete[] textures;
}


uint32_t TexturesController::AddTexture(const char *filePath)
{
	for (uint8_t i = 0; i < textures->size(); i++)
		if ((*textures)[i]->IsEqualFilePath(filePath)) 
			return i + 1;

	std::string ext;
	for (int i = strlen(filePath) - 1; i > 0; i--)
	{
		if (filePath[i] == '.')
			break;
		ext = filePath[i] + ext;
	}
	std::vector<uint8_t> *image;
	uint32_t width, height;
	uint32_t error;
	int format, internalFormat;

	if (strcmpi(ext.c_str(), "png"))
	{
		error = lodepng::decode(*image, width, height, filePath);
		if (error != 0)
		{
			std::cout << "\nerror " << error << ": " << lodepng_error_text(error) << std::endl;
			return 0;
		}
		format = GL_RGBA;
		internalFormat = GL_RGBA;
	}
	else if (strcmpi(ext.c_str(), "tga"))
	{
		error = LoadTGA(image, &width, &height, &internalFormat, &format, filePath);
		if (error < 0)
			return 0;
	}
	uint32_t textureId;

	// �������� � OpenGL ��������� ������ ��������
	glGenTextures(1, &textureId);

	// ������� �������� ��������
	glBindTexture(GL_TEXTURE_2D, textureId);

	// ��������� ��������� ���������� �������� - �������� ����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// ��������� ��������� "�������������" �������� - ���������� ������������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// �������� ������ � ����� � ������� �������� ��������
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, &image[0]);

	textures->push_back(new Texture(image, filePath, textureId, width, height));
	delete image;

	return textureId;
}

uint32_t TexturesController::GetTextureWidth(uint32_t textureId)
{
	return (*textures)[textureId-1]->GetWidth();
}

uint32_t TexturesController::GetTextureHeight(uint32_t textureId)
{
	return (*textures)[textureId - 1]->GetHeight();
}


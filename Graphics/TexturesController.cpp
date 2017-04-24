#include "TexturesController.h"
#include "GraphicsResources.h"


TexturesController::TexturesController()
{
	textures = new std::vector<Texture*>();
}


TexturesController::~TexturesController()
{
	for (uint32_t i = 0; i < textures->size(); i++)
	{
		delete (*textures)[i];
	}
	delete[] textures;
}


uint32_t TexturesController::AddTexture(const char *filePath)
{
	for (uint32_t i = 0; i < textures->size(); i++)
		if ((*textures)[i]->IsEqualFilePath(filePath)) 
			return i + 1;

	std::string ext;
	for (int i = strlen(filePath) - 1; i > 0; i--)
	{
		if (filePath[i] == '.')
			break;
		ext = filePath[i] + ext;
	}
	std::vector<uint8_t> *image = new std::vector<uint8_t>();
	uint32_t width, height;
	uint32_t error;
	std::string fullFilePath;
	fullFilePath.append(GraphicsResources::texturesFolderPath);
	fullFilePath.append(filePath);
	int format, internalFormat;

	//std::cout << "\next: " << ext.c_str();

	if (stricmp(ext.c_str(), "png") == 0)
	{
		error = lodepng::decode(*image, width, height, fullFilePath.c_str());
		if (error != 0)
		{
			std::cout << "\nload error " << error << ": " << lodepng_error_text(error) << ": \"" << fullFilePath.c_str() << "\"";
			return 0;
		}
		format = GL_RGBA;
		internalFormat = GL_RGBA;
	}
	else if (stricmp(ext.c_str(), "tga") == 0)
	{
		error = LoadTGA(image, (int*)&width, (int*)&height, &internalFormat, &format, filePath);
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
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, &(*image)[0]);

	textures->push_back(new Texture(image, filePath, textureId, width, height));
	std::cout << "\nTexture loaded: \"" << fullFilePath.c_str() << "\"";

	delete image;
	return textureId;
}

int TexturesController::GetTextureWidth(uint32_t textureId)
{
	return textureId - 1 < textures->size() ? (*textures)[textureId-1]->GetWidth() : 0;
}

int TexturesController::GetTextureHeight(uint32_t textureId)
{
	return textureId - 1 < textures->size() ? (*textures)[textureId - 1]->GetHeight() : 0;
}



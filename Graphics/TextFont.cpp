#include "TextFont.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>


void TextFont::DrawText(std::string text, int size, glm::vec4 *color, float x, float y, glm::mat4 *projection, SdfTextShader *sdfTextShader)
{
	float sizeCoeff = size * 1.f / fontSize;
	model = glm::translate(glm::vec3(x, y, 0));
	model = glm::scale(model, glm::vec3(sizeCoeff));
	uint16_t glyph;

	for (uint32_t i = 0; i < text.size(); i++)
	{
		for (int j = 0; j < glyphsCount; j++)
		{
			glyph = (text[i] < 0 ? 256 : 0) + text[i];

			if (glyph == '\n') 
			{
				model[3].x = x;
				model = glm::translate(model, glm::vec3(0, -fontSize, 0));
				break;
			}
			if (glyph == glyphs[j].id)
			{
				model = glm::translate(model, glm::vec3(glyphs[j].width/2 , -glyphs[j].height/2, 0));
				model = glm::translate(model, glm::vec3(glyphs[j].xOffset, -glyphs[j].yOffset, 0));
				sprite->SetTextureShape(glyphs[j].x, glyphs[j].y, glyphs[j].width, glyphs[j].height);

				sprite->SetColor(color);
				sprite->Draw(&model, projection, &glm::mat4(1));

				model = glm::translate(model, glm::vec3(-glyphs[j].xOffset, glyphs[j].yOffset, 0));
				model = glm::translate(model, glm::vec3(-glyphs[j].width / 2, glyphs[j].height/2, 0));
				model = glm::translate(model, glm::vec3(glyphs[j].xAdvance, 0, 0));
				break;
			}
		}
	}
}


TextFont::TextFont(const char* filePath)
{
	LoadFont(filePath);
	model = glm::mat4(1);
}


TextFont::~TextFont()
{
}

void TextFont::LoadFont(const char *filePath)
{
	uint32_t headerSize = 5;
	uint8_t  *buffer;
	uint32_t size;

	if (!FilesIOLibrary::LoadFile(filePath, &buffer, &size))
	{
		std::cout << "\nLoading font error";
		return;
	}

	uint32_t infoBlockLength = *(uint32_t*)&buffer[headerSize];
	uint32_t commonBlockLength = *(uint32_t*)&buffer[headerSize + 5 + infoBlockLength];
	uint32_t pagesBlockLength = *(uint32_t*)&buffer[headerSize + 5 + infoBlockLength + 5 + commonBlockLength];
	uint32_t charsBlockLength = *(uint32_t*)&buffer[headerSize + 5 + infoBlockLength + 5 + commonBlockLength + 5 + pagesBlockLength];

	fontSize = abs(*(int16_t*)&buffer[headerSize + 4]);

	lineHeight = *(uint16_t*)&buffer[headerSize + 5 + infoBlockLength + 4];

	base = *(uint16_t*)&buffer[headerSize + 5 + infoBlockLength + 4 + 2];

	char *textureFileName = (char*)malloc(sizeof(char) * pagesBlockLength);

	for (uint32_t i = 0; i < pagesBlockLength; i++)
	{
		textureFileName[i] = *(uint8_t*)&buffer[headerSize + 5 + infoBlockLength + 5 + commonBlockLength + 4 + i];
	}

	using namespace std;

	string folderPath;
	bool isFolderPathStart = false;
	for(int i = strlen(filePath) - 1; i >= 0; i--)
	{
		if (!isFolderPathStart)
		{
			if (filePath[i] == '\\')
				isFolderPathStart = true;
		}
		else
		{
			folderPath = filePath[i] + folderPath;
		}
	}

	folderPath += textureFileName;

	sprite = new SDFChar();

	glyphsCount = charsBlockLength / 20;

	glyphs = (Glyph*)malloc(sizeof(Glyph) * glyphsCount);
	for (uint32_t i = 0; i < glyphsCount; i++)
	{
		glyphs[i] = *(Glyph*)&buffer[headerSize + 5 + infoBlockLength + 5 + commonBlockLength + 5 + pagesBlockLength + 4 + i * 20];
	}
	delete[] buffer;
}

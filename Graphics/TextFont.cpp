#include "TextFont.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>


void TextFont::DrawText(std::string text, int size, glm::vec4 *color, float x, float y, glm::mat4 *projection, SpriteShader *spriteShader)
{
	float sizeCoeff = size * 1.f / fontSize;
	model = glm::translate(glm::vec3(x, y, 0));
	model = glm::scale(model, glm::vec3(sizeCoeff));

	for (uint32_t i = 0; i < text.size(); i++)
	{
		for (int j = 0; j < glyphsCount; j++)
		{
			if (text[i] == '\n')
			{
				model[3].x = 0;
				model = glm::translate(model, glm::vec3(0, -fontSize, 0));
				break;
			}
			if (text[i] == glyphs[j].id)
			{
				model = glm::translate(model, glm::vec3(glyphs[j].width/2 , -glyphs[j].height/2, 0));
				model = glm::translate(model, glm::vec3(glyphs[j].xOffset, -glyphs[j].yOffset, 0));
				sprite->SetShape(glyphs[j].x, glyphs[j].y, glyphs[j].width, glyphs[j].height);
				sprite->SetColor(color);
				sprite->Draw(&model, projection, &glm::mat4(1), spriteShader);
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
	LoadFile(filePath, true, &buffer, &size);
	uint32_t infoBlockLength = *(uint32_t*)&buffer[headerSize];
	uint32_t commonBlockLength = *(uint32_t*)&buffer[headerSize + 5 + infoBlockLength];
	uint32_t pagesBlockLength = *(uint32_t*)&buffer[headerSize + 5 + infoBlockLength + 5 + commonBlockLength];
	uint32_t charsBlockLength = *(uint32_t*)&buffer[headerSize + 5 + infoBlockLength + 5 + commonBlockLength + 5 + pagesBlockLength];
	fontSize = abs(*(int16_t*)&buffer[headerSize + 4]);
	lineHeight = *(uint16_t*)&buffer[headerSize + 5 + infoBlockLength + 4];
	base = *(uint16_t*)&buffer[headerSize + 5 + infoBlockLength + 4 + 2];
	char *textureFilePath = (char*)malloc(sizeof(char) * pagesBlockLength);
	for (uint32_t i = 0; i < pagesBlockLength; i++)
	{
		textureFilePath[i] = *(uint8_t*)&buffer[headerSize + 5 + infoBlockLength + 5 + commonBlockLength + 4 + i];
	}

	using namespace std;
	vector<string> elems;
	stringstream ss(filePath);
	string item;
	while (getline(ss, item, '/'))
	{
		elems.push_back(item);
	}
	string folderPath;
	for (uint32_t i = 0; i < elems.size()-1; i++)
	{
		folderPath += elems[i] + '/';
	}
	folderPath += textureFilePath;
	sprite = new Sprite(&folderPath[0]);

	glyphsCount = charsBlockLength / 20;

	glyphs = (Glyph*)malloc(sizeof(Glyph) * glyphsCount);
	for (uint32_t i = 0; i < glyphsCount; i++)
	{
		glyphs[i] = *(Glyph*)&buffer[headerSize + 5 + infoBlockLength + 5 + commonBlockLength + 5 + pagesBlockLength + 4 + i * 20];
	}

}

bool TextFont::LoadFile(const char *fileName, bool binary, uint8_t **buffer, uint32_t *size)
{
	FILE     *input;
	uint32_t fileSize, readed;

	const char mode[] = { 'r', binary ? 'b' : 't', '\0' };

	if ((input = fopen(fileName, mode)) == NULL)
	{
		return false;
	}

	fseek(input, 0, SEEK_END);
	fileSize = (uint32_t)ftell(input);
	rewind(input);

	if (fileSize == 0)
	{
		fclose(input);
		return false;
	}

	*buffer = new uint8_t[fileSize];

	readed = fread(*buffer, 1, fileSize, input);

	fclose(input);

	if (readed != fileSize)
	{
		delete[] * buffer;
		return false;
	}

	*size = fileSize;

	return true;
}

#include "TextFont.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>


void TextFont::DrawText(std::wstring text, int size, glm::vec4 *color, float x, float y, glm::mat4 *projection)
{
	scale.x = -size * 1.f / fontSize;
	scale.y = -scale.x;
	scale.z = scale.y;
	sprite->SetScale(&scale);
	sprite->SetPosition(x, y);
	for (uint32_t i = 0, j = 0; i < text.size(); i++)
	{

		if (text[i] == L'\n')
		{
			//model[3].x = x;
			sprite->Translate(0, -fontSize);
			continue;
		}
		j = text[i] > 1000 ? (text[i] - 945 ): (text[i] - 32);
		sprite->Translate(glyphs[j].width / 2 * scale.y, -glyphs[j].height / 2 * scale.y);
		sprite->Translate(glyphs[j].xOffset * scale.y, -glyphs[j].yOffset* scale.y);

		sprite->SetTextureShape(glyphs[j].x, glyphs[j].y, glyphs[j].width, glyphs[j].height);
		sprite->SetColor(color);
		sprite->Draw(projection, &glm::mat4(1));

		sprite->Translate(-glyphs[j].xOffset* scale.y, glyphs[j].yOffset* scale.y);
		sprite->Translate(-glyphs[j].width / 2 * scale.y, glyphs[j].height / 2 * scale.y);
		sprite->Translate(glyphs[j].xAdvance * scale.y, 0);
	}
}


TextFont::TextFont(const char* filePath)
{
	LoadFont(filePath);
}


TextFont::~TextFont()
{
	free(glyphs);
	delete sprite;
}

void TextFont::ShowInfo()
{
	printf("\nTexture size:%dx%d", sprite->width, sprite->height);
	for (int i = 0; i < glyphsCount; i++)
	{
		printf("\nGlyph %d id:%d, x:%d, y:%d, w:%d, h:%d", i, glyphs[i].id, glyphs[i].x, glyphs[i].y, glyphs[i].width, glyphs[i].height);
	}
}

void TextFont::AddParamValue(glm::vec4 *delta)
{
	sprite->AddParams(delta);
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

	fontSize = abs(*(int16_t*)&buffer[headerSize + 4])/8;

	lineHeight = (*(uint16_t*)&buffer[headerSize + 5 + infoBlockLength + 4])/8;

	base = (*(uint16_t*)&buffer[headerSize + 5 + infoBlockLength + 4 + 2])/8;

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
	
	folderPath = folderPath + '\\' + textureFileName;

	sprite = new SDFChar(&glm::vec2(0.3, 20));
	sprite->SetShader("SDFText.vs", "SDFText.fs");
	sprite->SetTexture(folderPath.c_str(), false);
	sprite->SetBorder(&glm::vec4(0, 0, 0, 1), &glm::vec2(0.3, 20));

	glyphsCount = charsBlockLength / 20;

	glyphs = (Glyph*)malloc(sizeof(Glyph) * glyphsCount);
	for (uint32_t i = 0; i < glyphsCount; i++)
	{
		glyphs[i] = *(Glyph*)&buffer[headerSize + 5 + infoBlockLength + 5 + commonBlockLength + 5 + pagesBlockLength + 4 + i * 20];
		glyphs[i].height /= 8;
		glyphs[i].width /= 8;
		glyphs[i].x /= 8;
		glyphs[i].y /= 8;
		glyphs[i].xOffset /= 8;
		glyphs[i].yOffset /= 8;
		glyphs[i].xAdvance /= 8;
	}

	free(textureFileName);
	delete[] buffer;
}

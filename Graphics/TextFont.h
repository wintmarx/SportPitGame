#pragma once
#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport) 
#else
#define GRAPHICS_API __declspec(dllimport)
#endif
#include "GLHeaders.h"
#include "SdfTextShader.h"
#include <string>
#include "../FilesIOLibrary/FilesIOLibrary.h"


struct Glyph
{
	uint32_t id;
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	int16_t xOffset;
	int16_t yOffset;
	int16_t xAdvance;
};

class TextFont
{
public:
	GRAPHICS_API void DrawText(std::string text, int size, glm::vec4 *color, float x, float y, glm::mat4 *projection, SdfTextShader *spriteShader);
	GRAPHICS_API TextFont(const char* filePath);
	GRAPHICS_API ~TextFont();
	uint8_t *fontName;
private:
	void LoadFont(const char *filePath);
	bool LoadFile(const char *fileName, bool binary, uint8_t **buffer, uint32_t *size);
	Glyph *glyphs;
	uint32_t glyphsCount;
	int16_t fontSize;
	uint16_t lineHeight;
	uint16_t base;
	glm::mat4 model;
};


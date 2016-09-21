#pragma once
#include "GLHeaders.h"
#include "Sprite.h"
#include <string>

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
	__declspec(dllexport) void DrawText(std::string text, int size, glm::vec4 *color, float x, float y, glm::mat4 *projection, SpriteShader *spriteShader);
	__declspec(dllexport) TextFont(const char* filePath);
	__declspec(dllexport) ~TextFont();
private:
	void LoadFont(const char *filePath);
	bool LoadFile(const char *fileName, bool binary, uint8_t **buffer, uint32_t *size);
	Sprite *sprite;
	Glyph *glyphs;
	uint32_t glyphsCount;
	int16_t fontSize;
	uint16_t lineHeight;
	uint16_t base;
	glm::mat4 model;
};


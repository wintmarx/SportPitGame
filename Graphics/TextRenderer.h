#pragma once
#include <vector>
#include "TextFont.h"
#include <string>

class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer();
	void DrawText(std::string text, float x, float y, int size, std::string Font);
	void DrawText(std::string text, float x, float y, int size, std::string Font, int rectColor);
	void DrawText(std::string text, float x, float y, int size, std::string Font, int outlineColor, int outlineWidth);
private:
	std::vector<TextFont*> *fontsList;
};


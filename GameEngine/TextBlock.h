#pragma once
#include "..\Includes\glm\glm.hpp"
#include "..\Includes\glm\gtx\transform.hpp"
#include <string>
#include <vector>


struct OutputTextBlock
{
	uint32_t x;
	uint32_t y;
	std::string fontFilePath;
};

class TextBlock
{
public:
	TextBlock(std::string *text, int fontSize, glm::vec4 *color, float x, float y);
	float x;
	float y;
	int fontSize;
	std::string text;
	std::string fontFilePath;
	std::vector<OutputTextBlock*> outputs;
	glm::vec4 color;
};


#include "TextBlock.h"


TextBlock::TextBlock(std::string *text, int fontSize, glm::vec4 *color, float x, float y)
{
	this->x = x;
	this->y = y;
	this->fontSize = fontSize;
	this->text = *text;
	//this->font = font;
	this->color = *color;
}

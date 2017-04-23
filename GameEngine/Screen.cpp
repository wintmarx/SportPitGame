#include "Screen.h"
#include "ScreenController.h"



Screen::Screen(int width, int height)
{
	this->width = width;
	this->height = height;
}


Screen::~Screen()
{
}

void Screen::SetScreenController(ScreenController *screenController)
{ 
	Screen::screenController = screenController; 
}

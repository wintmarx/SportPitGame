#include <iostream>
#include <vector>
#include "GameScreen.h"
#include "MenuScreen.h"
#include "../GameEngine/ScreenController.h"

void main()
{
	ScreenController *screenController;
	int screenWidth = 840;
	int screenHeight = 480;
	screenController = new ScreenController(screenWidth, screenHeight, new std::string("SportPit Game"));
	screenController->AddScreen(new MenuScreen(screenWidth, screenHeight));
	screenController->StartMainLoop();
	delete screenController;
}




#include <iostream>
#include <vector>
#include "GameScreen.h"
#include "MenuScreen.h"
#include "../GameEngine/ScreenController.h"

void main()
{
	ScreenController *screenController;
	int screenWidth = 800;
	int screenHeight = 800;
	screenController = new ScreenController(screenWidth, screenHeight, new std::string("SportPit Game"));
	screenController->AddScreen(new MenuScreen(screenWidth, screenHeight));
	screenController->StartMainLoop();
	delete screenController;
}




#include <iostream>
#include <vector>
#include "GameScreen.h"
#include "MainScreen.h"
#include "../GameEngine/ScreenController.h"

void main()
{
	ScreenController *screenController;
	int screenWidth = 800;
	int screenHeight = 700;
	screenController = new ScreenController(screenWidth, screenHeight, new std::string("SportPit Game"));
	screenController->AddScreen(new MainScreen(screenWidth, screenHeight));
	screenController->StartMainLoop();
	delete screenController;
}




#pragma once
#include "..\GameEngine\Screen.h"
#include "Player.h"
#include "Food\Banana.h"
#include "Food\Cola.h"
#include "Food\Banana.h"
#include "Food\Donut.h"
#include "Food\Croissant.h"
#include "Food\Burger.h"
#include "Food\Food.h"
#include <vector>
#include <string>
#include <ctime>
#include "GasSimulationScreen.h"

class GameScreen :
	public Screen
{
public:
	GameScreen(int width, int height);
	~GameScreen();
	void Update(float delta);
	void Render(Graphics *graphics);
	void OnKeyPress(int buttonID, bool isPressed);
	void OnKeyRelease(int buttonID);
	void Initialize();
private:
	void LoadLayout(const char *filePath);
	glm::vec3 cameraPosition;
	glm::vec3 cameraZoom;
	bool isStop = false;
	Player *player;
	std::vector<Food*> food;
	const int cellsCount = 30;
	int fieldSize;
	std::string FPS;
};


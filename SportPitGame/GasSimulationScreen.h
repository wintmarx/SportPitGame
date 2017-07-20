#pragma once
#include "..\GameEngine\Screen.h"
#include "Player.h"
#include "Food\Burger.h"
#include "Food\Food.h"

class GasSimulationScreen : public Screen
{
public:
	GasSimulationScreen(int width, int height);
	virtual ~GasSimulationScreen();
	void Update(float delta);
	void Render(Graphics *graphics);
	void OnKeyPress(int buttonID, bool isPressed);
	void OnKeyRelease(int buttonID);
	void Initialize();
	void Collider(Unit **donuts);
};



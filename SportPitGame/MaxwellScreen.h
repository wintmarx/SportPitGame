#pragma once
#include "..\GameEngine\Screen.h"

class MaxwellScreen :
	public Screen
{
public:
	MaxwellScreen(int width, int height);
	virtual ~MaxwellScreen();
	void Update(float delta);
	void Render(Graphics *graphics);
	void OnKeyPress(int buttonID, bool isPressed);
	void OnKeyRelease(int buttonID);
	void Initialize();
	double maxwellFunc(double v, double v0);
	double v0;
};


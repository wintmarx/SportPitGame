#include "MaxwellScreen.h"
#include "MenuScreen.h"
#include "../Graphics/TextFont.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include "iostream"


using namespace glm;
double v0;
MaxwellScreen::MaxwellScreen(int width, int height) : Screen(width, height)
{
	glClearColor(.1f, .67f, 1.f, 1.f);

	projection = ortho(0.0f, width * 1.0f, 0.0f, height*1.0f, 1.0f, -1.0f);

	v0 = 300;
}


MaxwellScreen::~MaxwellScreen()
{
}

void MaxwellScreen::Update(float delta)
{
	 
}

double MaxwellScreen::maxwellFunc(double v, double v0)
{
	return 2 * v / (v0 * v0) * exp(-v*v / (v0 * v0));
}
void MaxwellScreen::Render(Graphics *graphics)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//graphics->DrawLine(100, 200, 100, 300, &glm::vec4(1.0f, 1.0f, 1, 1.0f), &projection);
	//graphics->DrawLine(100, 300, 200, 250, &glm::vec4(1.0f, 1.0f, 1, 1.0f), &projection);
	//graphics->DrawLine(200, 250, 300, 300, &glm::vec4(1.0f, 1.0f, 1, 1.0f), &projection);
	//graphics->DrawLine(300, 300, 300, 200, &glm::vec4(1.0f, 1.0f, 1, 1.0f), &projection);

	double y;
	int h = 3;

	for (int i = 0; i < 60 * h; i+=h)
	{
		y = 300;//maxwellFunc(i, v0) * 200000;
		graphics->DrawLine(i, 0, i, y, &glm::vec4(1, 0, 0, 1), &projection);
		//graphics->DrawLine(donuts[i]->position.x, donuts[i]->position.y, donuts[i]->position.x + donuts[i]->direction.x * donuts[i]->velocity, donuts[i]->position.y + donuts[i]->direction.y * donuts[i]->velocity, new vec4(1, 1, 0, 1), &projection);
	}
	////std::cout << v0 << std::endl;
}

void MaxwellScreen::OnKeyPress(int buttonID, bool isPressed)
{
	switch (buttonID)
	{
	case GLFW_KEY_BACKSPACE:
		if (!isPressed)
			Screen::screenController->PreviousScreen();
		break;
	case GLFW_KEY_EQUAL:
			v0 +=5;
		break;
	case GLFW_KEY_MINUS:
			v0 -=5;
		break;
	}
}

void MaxwellScreen::OnKeyRelease(int buttonID)
{

}

void MaxwellScreen::Initialize()
{

}

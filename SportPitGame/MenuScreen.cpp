#include "MenuScreen.h"
#include "GameScreen.h"


using namespace glm;


MenuScreen::MenuScreen(int width, int height) : Screen(width, height)
{
	glClearColor(.1f, .67f, 1.f, 1.f);

	projection = ortho(0.0f, width * 1.0f, 0.0f, height*1.0f, 1.0f, -1.0f);
}


MenuScreen::~MenuScreen()
{

}

void MenuScreen::Update(float delta)
{

}

void MenuScreen::Render(Graphics *graphics)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	graphics->DrawLine(100, 200, 250, 200, &glm::vec4(1.0f, 1.0f, 0, 1.0f), &projection);
}

void MenuScreen::OnKeyPress(int buttonID, bool isPressed)
{
	switch (buttonID)
	{
	case GLFW_KEY_SPACE:
		if (!isPressed)
			Screen::screenController->AddScreen(new GameScreen(width, height));
	}
}

void MenuScreen::OnKeyRelease(int buttonID)
{

}

void MenuScreen::Initialize()
{

}

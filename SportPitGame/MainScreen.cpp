#include "MainScreen.h"
#include "../Graphics/TextFont.h"
#include "../Graphics/CommonSprite.h"
#include "Food\Burger.h"
#include "../GameEngine/Unit.h"


using namespace glm;
CommonSprite *sprite;
MainScreen::MainScreen(int width, int height) : Screen(width, height)
{
	glClearColor(.1f, .67f, 1.f, 1.f);
	projection = ortho(0.0f, width * 1.0f, 0.0f, height*1.0f, 1.0f, -1.0f);
	view = mat4(1);
	sprite = new CommonSprite(400, 300);
	sprite->SetTexture("arial_0.png");
	sprite->SetColor(new vec4(1, 1, 0, 1));
	sprite->SetShader("SDFText.vs", "SDFText.fs");
}


MainScreen::~MainScreen()
{
}

void MainScreen::Update(float delta)
{

}

void MainScreen::Render(Graphics *graphics)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	graphics->DrawLine(100, 200, 200, 300, new vec4(1, 1, 0, 1), &projection);
	sprite->Draw(&projection, &view);
	//std::cout << glGetError() << std::endl;
}

void MainScreen::OnKeyPress(int buttonID, bool isPressed)
{

}

void MainScreen::OnKeyRelease(int buttonID)
{

}

void MainScreen::Initialize()
{

}

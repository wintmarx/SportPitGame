#include "MainScreen.h"
#include "..\Graphics\TextFont.h"
#include "..\Graphics\CommonSprite.h"
#include "Food\Burger.h"
#include "..\GameEngine\Unit.h"


using namespace glm;
int textSize;
TextFont *font;
MainScreen::MainScreen(int width, int height) : Screen(width, height)
{
	glClearColor(.1f, .67f, 1.f, 1.f);
	projection = ortho(0.0f, width * 1.0f, 0.0f, height*1.0f, 1.0f, -1.0f);
	view = mat4(1);
	textSize = 36;
	font = new TextFont("..\\Data\\Fonts\\Calibri\\calibri.fnt");
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
	graphics->DrawLine(100, 600, 0, 0, &vec4(1, 1, 0, 1), &projection);
	font->DrawText(L" ¿“ﬂ ÀŒœ”’ ¿ ﬂ œ»ÿ” “≈ —“! ‚ 3:06 ÌÓ˜Ë", textSize, &vec4(1, 0, 0, 0), 100, 600, &projection);
	//std::cout << glGetError() << std::endl;
}

void MainScreen::OnKeyPress(int buttonID, bool isPressed)
{
	switch (buttonID)
	{
	case GLFW_KEY_Q:
		if (!isPressed)
		{
			font->AddParamValue(&glm::vec4(-0.05, 0 ,0 ,0 ));
		}
		break;
	case GLFW_KEY_W:
		if (!isPressed)
		{
			font->AddParamValue(&glm::vec4(0.05, 0, 0, 0));
		}
		break;
	case GLFW_KEY_E:
		//if (!isPressed)
		//{
			font->AddParamValue(&glm::vec4(0, -1, 0, 0));
		//}
		break;
	case GLFW_KEY_R:
		//if (!isPressed)
		//{
			font->AddParamValue(&glm::vec4(0, 1, 0, 0));
		//}
		break;
	case GLFW_KEY_A:
		if (!isPressed)
		{
			font->AddParamValue(&glm::vec4(0, 0, -0.05, 0));
		}
		break;
	case GLFW_KEY_S:
		if (!isPressed)
		{
			font->AddParamValue(&glm::vec4(0, 0, 0.05, 0));
		}
		break;
	case GLFW_KEY_D:
		//if (!isPressed)
		//{
			font->AddParamValue(&glm::vec4(0, 0, 0, -1));
		//}
		break;
	case GLFW_KEY_F:
		//if (!isPressed)
		//{
			font->AddParamValue(&glm::vec4(0, 0, 0, 1));
		//}
		break;
	case GLFW_KEY_EQUAL:
		//if (!isPressed)
		//{
			textSize++;
		//}
		break;
	case GLFW_KEY_MINUS:
		//if (!isPressed)
		//{
			textSize--;
		//}
		break;
	}
}

void MainScreen::OnKeyRelease(int buttonID)
{

}

void MainScreen::Initialize()
{

}

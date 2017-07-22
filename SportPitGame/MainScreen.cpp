#include "MainScreen.h"
#include "../Graphics/TextFont.h"
#include "../Graphics/CommonSprite.h"
#include "Food\Burger.h"
#include "../GameEngine/Unit.h"


using namespace glm;
SDFChar *sdfChar;
glm::vec4 params;
glm::vec3 fontScale;
MainScreen::MainScreen(int width, int height) : Screen(width, height)
{
	glClearColor(.1f, .67f, 1.f, 1.f);
	projection = ortho(0.0f, width * 1.0f, 0.0f, height*1.0f, 1.0f, -1.0f);
	view = mat4(1);
	params = vec4(0);
	fontScale = vec3(1);
	sdfChar = new SDFChar('A', new glm::vec2(0.3, 20));
	sdfChar->SetPosition(300, 400);
	sdfChar->SetTexture("arial_0.png");
	sdfChar->SetColor(new vec4(1, 1, 0, 1));
	sdfChar->SetBorder(new vec4(1, 0, 0, 1), new glm::vec2(0.3, 20));
	sdfChar->SetShader("SDFText.vs", "SDFText.fs");
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
	sdfChar->Draw(&projection, &view);
	//std::cout << glGetError() << std::endl;
}

void MainScreen::OnKeyPress(int buttonID, bool isPressed)
{
	switch (buttonID)
	{
	case GLFW_KEY_Q:
		if (!isPressed)
		{
			params.x -= 0.05;
			sdfChar->SetParams(&params);
			printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
		}
		break;
	case GLFW_KEY_W:
		if (!isPressed)
		{
			params.x += 0.05;
			sdfChar->SetParams(&params);
			printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
		}
		break;
	case GLFW_KEY_E:
		if (!isPressed)
		{
			params.y -= 1;
			sdfChar->SetParams(&params);
			printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
		}
		break;
	case GLFW_KEY_R:
		if (!isPressed)
		{
			params.y += 1;
			sdfChar->SetParams(&params);
			printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
		}
		break;
	case GLFW_KEY_A:
		if (!isPressed)
		{
			params.z -= 0.05;
			sdfChar->SetParams(&params);
			printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
		}
		break;
	case GLFW_KEY_S:
		if (!isPressed)
		{
			params.z += 0.05;
			sdfChar->SetParams(&params);
			printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
		}
		break;
	case GLFW_KEY_D:
		if (!isPressed)
		{
			params.w -= 1;
			sdfChar->SetParams(&params);
			printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
		}
		break;
	case GLFW_KEY_F:
		if (!isPressed)
		{
			params.w += 1;
			sdfChar->SetParams(&params);
			printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
		}
		break;
	case GLFW_KEY_EQUAL:
		if (!isPressed)
		{
			fontScale += glm::vec3(1);
			sdfChar->Scale(&fontScale);
			printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
		}
		break;
	case GLFW_KEY_MINUS:
		if (!isPressed)
		{
			fontScale -= glm::vec3(1);
			sdfChar->Scale(&fontScale);
			printf("\n%f\t| %f\t| %f\t| %f", params.x, params.y, params.z, params.w);
		}
		break;
	}
}

void MainScreen::OnKeyRelease(int buttonID)
{

}

void MainScreen::Initialize()
{

}

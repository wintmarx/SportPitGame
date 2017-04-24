#include "MenuScreen.h"
#include "GameScreen.h"
#include "MaxwellScreen.h"
#include "../Graphics/TextFont.h"
#include "Food\Donut.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include "iostream"


using namespace glm;

std::vector<Unit*> donuts;
float *positionsX;
float *positionsY;
int count;
double timeTicks;
double deltaTime;
int currentTime;
std::ofstream simFile;
MenuScreen::MenuScreen(int width, int height) : Screen(width, height)
{
	glClearColor(.1f, .67f, 1.f, 1.f);

	projection = ortho(0.0f, width * 1.0f, 0.0f, height*1.0f, 0.f, 1.0f);


	srand(time(0));

}


MenuScreen::~MenuScreen()
{
}

void MenuScreen::Collider(Unit **donuts)
{
	double distance;
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{

			distance = glm::length(donuts[i]->position - donuts[j]->position);

			if (distance < donuts[i]->GetWidth())
			{
				glm::vec3 normalAxis = donuts[j]->position - donuts[i]->position;
				double sina = (normalAxis.y < 0 ? normalAxis.y * -1 : normalAxis.y) / distance;
				if (normalAxis.x < 0 && normalAxis.y < 0 || normalAxis.x > 0 && normalAxis.y > 0) 
					sina *= -1;
				double cosa = (normalAxis.x < 0 ? normalAxis.x * -1 : normalAxis.x) / distance;

				double tmpx = donuts[i]->direction.x * donuts[i]->velocity;
				double tmpy = donuts[i]->direction.y * donuts[i]->velocity;

				donuts[i]->direction.x = tmpx * cosa - tmpy * sina;
				donuts[i]->direction.y = tmpx * sina + tmpy * cosa;

				tmpx = donuts[j]->direction.x * donuts[j]->velocity;
				tmpy = donuts[j]->direction.y * donuts[j]->velocity;
				donuts[j]->direction.x = tmpx * cosa - tmpy * sina;
				donuts[j]->direction.y = tmpx * sina + tmpy * cosa;

				tmpy = donuts[i]->direction.x;
				donuts[i]->direction.x = donuts[j]->direction.x;
				donuts[j]->direction.x = tmpy;

				tmpx = donuts[i]->direction.x;
				tmpy = donuts[i]->direction.y;
				donuts[i]->direction.x = tmpx * cosa + tmpy * sina;
				donuts[i]->direction.y = -tmpx * sina + tmpy * cosa;
				tmpx = donuts[i]->direction.x;
				tmpy = donuts[i]->direction.y;
				donuts[i]->velocity = sqrt(tmpx * tmpx + tmpy * tmpy);
				donuts[i]->direction = glm::normalize(donuts[i]->direction);

				tmpx = donuts[j]->direction.x;
				tmpy = donuts[j]->direction.y;
				donuts[j]->direction.x = tmpx * cosa + tmpy * sina;
				donuts[j]->direction.y = -tmpx * sina + tmpy * cosa;
				donuts[j]->velocity = sqrt(tmpx * tmpx + tmpy * tmpy);
				donuts[j]->direction = glm::normalize(donuts[j]->direction);

				glm::vec3 center = (donuts[i]->position + donuts[j]->position) / 2.f;
				donuts[i]->position = center + glm::normalize(donuts[i]->position - center) * (donuts[i]->GetWidth() / 2.f);
				donuts[j]->position = center + glm::normalize(donuts[j]->position - center) * (donuts[j]->GetWidth() / 2.f);
			}
		}

		if (donuts[i]->position.y + donuts[i]->GetHeight() / 2. >= height)
		{
			donuts[i]->direction.y *= -1;
			donuts[i]->position.y = height - donuts[i]->GetHeight() / 2.;
		}
		else if (donuts[i]->position.y - donuts[i]->GetHeight() / 2. <= 0)
		{
			donuts[i]->direction.y *= -1;
			donuts[i]->position.y = donuts[i]->GetHeight() / 2.;
		}
		if (donuts[i]->position.x + donuts[i]->GetWidth() / 2. >= width)
		{
			donuts[i]->direction.x *= -1;
			donuts[i]->position.x = width - donuts[i]->GetWidth() / 2.;
		}
		else if (donuts[i]->position.x - donuts[i]->GetWidth() / 2. <= 0)
		{
			donuts[i]->direction.x *= -1;
			donuts[i]->position.x = donuts[i]->GetWidth() / 2.;
		}
	}
}

void MenuScreen::Update(float delta)
{
}

void MenuScreen::Render(Graphics *graphics)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//graphics->DrawLine(100, 200, 100, 300, &glm::vec4(1.0f, 1.0f, 0, 1.0f), &projection);
	//graphics->DrawLine(100, 300, 200, 250, &glm::vec4(1.0f, 1.0f, 0, 1.0f), &projection);
	//graphics->DrawLine(200, 250, 300, 300, &glm::vec4(1.0f, 1.0f, 0, 1.0f), &projection);
	//graphics->DrawLine(300, 300, 300, 200, &glm::vec4(1.0f, 1.0f, 0, 1.0f), &projection);

	for (int i = 0; i < count; i++)
	{
		if (currentTime < timeTicks)
		{
			donuts[i]->position.x = positionsX[count * currentTime + i];
			donuts[i]->position.y = positionsY[count * currentTime + i];
		}
		donuts[i]->Draw(&projection, &view, graphics);
		//graphics->DrawLine(donuts[i]->position.x, donuts[i]->position.y, donuts[i]->position.x + donuts[i]->direction.x * donuts[i]->velocity, donuts[i]->position.y + donuts[i]->direction.y * donuts[i]->velocity, new vec4(1, 1, 1, 1), &projection);
		//graphics->DrawLine(donuts[i]->position.x-1, donuts[i]->position.y, donuts[i]->position.x - 1 + donuts[i]->direction.x * donuts[i]->velocity, donuts[i]->position.y + donuts[i]->direction.y * donuts[i]->velocity, new vec4(1, 1, 1, 1), &projection);
		//graphics->DrawLine(donuts[i]->position.x + 1, donuts[i]->position.y, donuts[i]->position.x + 1 + donuts[i]->direction.x * donuts[i]->velocity, donuts[i]->position.y + donuts[i]->direction.y * donuts[i]->velocity, new vec4(1, 1, 1, 1), &projection);
	}
	//glBlendFunc();
	//for (int i = 1; i < 300 * 1; i += 30)
	//{
	//	graphics->DrawLine(100, i, 500, i+1, &glm::vec4(0, 0, 0, 1), &projection);
	//	//graphics->DrawLine(100, i, 500, i, &glm::vec4(1, 0, 0, 1), &projection);
	//	//graphics->DrawLine(donuts[i]->position.x, donuts[i]->position.y, donuts[i]->position.x + donuts[i]->direction.x * donuts[i]->velocity, donuts[i]->position.y + donuts[i]->direction.y * donuts[i]->velocity, new vec4(1, 1, 0, 1), &projection);
	//}
	currentTime++;
}

void MenuScreen::OnKeyPress(int buttonID, bool isPressed)
{
	switch (buttonID)
	{
	case GLFW_KEY_SPACE:
		if (!isPressed)
			Screen::screenController->AddScreen(new GameScreen(width, height));
		break;
	case GLFW_KEY_M: 
		if (!isPressed)
			Screen::screenController->AddScreen(new MaxwellScreen(width, height));
		break;
	case GLFW_KEY_R:
			currentTime = 0;
		break;
	case GLFW_KEY_S:
		if (!isPressed)
		{
			donuts.clear();
			printf("\nInput count of particals: ");
			std::cin >> count;
			double angle = 0;
			double size;
			printf("\nInput size of particals relative to screen: ");
			std::cin >> size;
			donuts = std::vector<Unit*>(count);
			for (int i = 0; i < count; i++)
			{
				donuts[i] = new Donut(height * size, height * size, new vec3(rand() * 1.f / RAND_MAX * width, rand() * 1.f / RAND_MAX  * height, 0));
				donuts[i]->velocity = 300;
				angle = rand()* 1.f / RAND_MAX * 2 * 3.1415;
				donuts[i]->direction.x = cos(angle);
				donuts[i]->direction.y = sin(angle);
			}
			float secCount;
			printf("\nInput duration of simulation: ");
			std::cin >> secCount;
			deltaTime = 1. / 60;
			timeTicks = secCount / deltaTime;
			positionsX = (float*)malloc(sizeof(float) * timeTicks * count);
			positionsY = (float*)malloc(sizeof(float) * timeTicks * count);
			simFile = std::ofstream("simulation.txt", std::ios_base::out);
			simFile << "c " << count << "\n";
			simFile << "s " << donuts[0]->GetWidth() << "\n";
			for (int i = 0; i < timeTicks; i++)
			{
				for (int j = 0; j < count; j++)
				{
					positionsX[i * count + j] = donuts[j]->position.x; 
					positionsY[i * count + j] = donuts[j]->position.y;
					simFile << "p " << donuts[j]->position.x << " " << donuts[j]->position.y << "\n";
					simFile << "d " << donuts[j]->direction.x << " " << donuts[j]->direction.y << "\n";
					simFile << "v " << donuts[j]->velocity << "\n";
					donuts[j]->Update(deltaTime);
				}
				Collider(&donuts[0]);
			}
			currentTime = 0;
			simFile.close();
		}
		break;
	}
}

void MenuScreen::OnKeyRelease(int buttonID)
{

}

void MenuScreen::Initialize()
{

}

#include "MaxwellScreen.h"
#include "MenuScreen.h"
#include "../Graphics/TextFont.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include "iostream"


using namespace glm;
double v0;
double *velocitiesHistogramValues;
int intervalsCount;
double deltaV;
std::ifstream simFile;
MaxwellScreen::MaxwellScreen(int width, int height) : Screen(width, height)
{
	glClearColor(.1f, .67f, 1.f, 1.f);
	projection = ortho(0.0f, width * 1.0f, 0.0f, height*1.0f, 1.0f, -1.0f);
	view = mat4(1);
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
	double x;
	double h = 1. * width / intervalsCount;

	for (int i = 0; i < intervalsCount; i++)
	{
		x = i * h;
		y = velocitiesHistogramValues[i] * 150000;

		graphics->DrawLine(x, 0, x, y, &glm::vec4(1, 1, 0, 1), &(projection*view));
		//graphics->DrawLine(x+1, 0, x+1, y, &glm::vec4(1, 1, 0, 1), &(projection*view));
		graphics->DrawLine(x, maxwellFunc(i * deltaV, v0) * 150000 - 2, x, maxwellFunc(i * deltaV, v0) * 150000, &glm::vec4(0, 0, 0, 1), &(projection*view));
	}

	h = width / 4. / v0;
	for (int i = 0; i < width; i++)
	{
		y = maxwellFunc(i * h, v0) * 150000;
		graphics->DrawLine(i, y - 2, i, y, &glm::vec4(1, 0, 0, 1), &(projection*view));
		//graphics->DrawLine(x, maxwellFunc(i * deltaV, v0) * 150000 - 2, x, maxwellFunc(i * deltaV, v0) * 150000, &glm::vec4(1, 0, 0, 1), &(projection*view));
		//graphics->DrawLine(x + 1, maxwellFunc(i * deltaV, v0) * 150000 - 2, x + 1, maxwellFunc(i * deltaV, v0) * 150000, &glm::vec4(1, 0, 0, 1), &(projection*view));
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
			view = scale(view,vec3(1.05,1.05,1));
		break;
	case GLFW_KEY_MINUS:
			view = scale(view,vec3(1./1.05, 1./1.05, 1));
		break;
	}
}

void MaxwellScreen::OnKeyRelease(int buttonID)
{

}

void MaxwellScreen::Initialize()
{
	printf("\nLoading Maxwell...");
	simFile.open("simulation.txt", std::ios_base::in);
	std::string line;
	std::string buff;
	std::getline(simFile, line);
	for (int i = 2; i < line.size(); i++)
	{
		buff.push_back(line[i]);
	}
	int count = atoi(&buff[0]);

	intervalsCount = 40;

	velocitiesHistogramValues = (double*)malloc(sizeof(double) * intervalsCount);
	for (int i = 0; i < intervalsCount; i++)
		velocitiesHistogramValues[i] = 0;

	int j = 0;
	int timeSteps = 0;

	v0 = 300;
	deltaV = 4 * v0 / intervalsCount;
	double tmpVelocity;

	while (!simFile.eof())
	{
		std::getline(simFile, line);
		if (line[0] == 'v')
		{
			buff.clear();
			for (int i = 2; i < line.size(); i++)
			{
				buff.push_back(line[i]);
			}
			tmpVelocity = atof(&buff[0]);

			for (int i = 0; i < intervalsCount; i++)
			{
				if (tmpVelocity >= i * deltaV && tmpVelocity <= (i + 1) * deltaV)
				{
					velocitiesHistogramValues[i]++;
					break;
				}
			}

			if (j%count == 0)
				timeSteps++;

			j++;
		}
	}

	for (int i = 0; i < intervalsCount; i++)
	{
		velocitiesHistogramValues[i] /=  (count * timeSteps * deltaV);
	}
	simFile.close();
}

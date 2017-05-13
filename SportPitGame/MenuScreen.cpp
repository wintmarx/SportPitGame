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
float *velocities;
int count;
double timeTicks;
float deltaTime;
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
				double sina = (normalAxis.y < 0 ? -normalAxis.y : normalAxis.y) / distance;
				if (normalAxis.x < 0 && normalAxis.y < 0 || normalAxis.x > 0 && normalAxis.y > 0) 
					sina *= -1;
				double cosa = (normalAxis.x < 0 ? -normalAxis.x : normalAxis.x) / distance;

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

		if (donuts[i]->position.y + donuts[i]->GetHeight() / 2.f >= height)
		{
			donuts[i]->direction.y *= -1;
			donuts[i]->position.y = height - donuts[i]->GetHeight() / 2.f;
		}
		else if (donuts[i]->position.y - donuts[i]->GetHeight() / 2.f <= 0)
		{
			donuts[i]->direction.y *= -1;
			donuts[i]->position.y = donuts[i]->GetHeight() / 2.f;
		}
		if (donuts[i]->position.x + donuts[i]->GetWidth() / 2.f >= width)
		{
			donuts[i]->direction.x *= -1;
			donuts[i]->position.x = width - donuts[i]->GetWidth() / 2.f;
		}
		else if (donuts[i]->position.x - donuts[i]->GetWidth() / 2.f <= 0)
		{
			donuts[i]->direction.x *= -1;
			donuts[i]->position.x = donuts[i]->GetWidth() / 2.f;
		}
	}
}

void MenuScreen::Update(float delta)
{
	for (int i = 0; i < count; i++)
	{
		if (currentTime < timeTicks)
		{
			donuts[i]->position.x = positionsX[count * currentTime + i];
			donuts[i]->position.y = positionsY[count * currentTime + i];
		}
	}
}

double impuls = 0;
double oldImpuls = 0;

double energy = 0;
double oldEnergy = 0;

void MenuScreen::Render(Graphics *graphics)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (currentTime < timeTicks)
	{
		oldImpuls = impuls;
		oldEnergy = energy;
		impuls = 0;
		energy = 0;
		for (int i = 0; i < count; i++)
		{
			donuts[i]->position.x = positionsX[count * currentTime + i];
			donuts[i]->position.y = positionsY[count * currentTime + i];
			impuls += velocities[count * currentTime + i];
			energy += velocities[count * currentTime + i] * velocities[count * currentTime + i];
			donuts[i]->Draw(&projection, &view, graphics);
		}
		printf("\nimpuls = %f", impuls);
		printf("\nenergy = %f", energy);
		currentTime++;
	}
	//printf("\nGLERROR: %i", glGetError());
}


void MenuScreen::OnKeyPress(int buttonID, bool isPressed)
{
	std::ifstream loadFile;
	std::string line;
	std::string buff;
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
	case GLFW_KEY_L:
		if (!isPressed)
		{
			printf("\nLoading Simulation...");
			loadFile.open("simulation.txt", std::ios_base::in);
			std::getline(loadFile, line);
			for (int i = 2; i < line.size(); i++)
			{
				buff.push_back(line[i]);
			}
			count = atoi(&buff[0]);

			buff.clear();
			std::getline(loadFile, line);
			for (int i = 2; i < line.size(); i++)
			{
				buff.push_back(line[i]);
			}
			timeTicks = atoi(&buff[0]);

			float particleSize = 0;
			buff.clear();
			std::getline(loadFile, line);
			for (int i = 2; i < line.size(); i++)
			{
				buff.push_back(line[i]);
			}
			particleSize = atof(&buff[0]);

			donuts = std::vector<Unit*>(count);
			for (int i = 0; i < count; i++)
			{
				donuts[i] = new Donut(particleSize, particleSize, new vec3(0));
			}

			positionsX = (float*)malloc(sizeof(float) * count * timeTicks);
			positionsY = (float*)malloc(sizeof(float) * count * timeTicks);
			velocities = (float*)malloc(sizeof(float) * timeTicks * count);

			int p = 0;
			while (!loadFile.eof())
			{
				std::getline(loadFile, line);
				if (line[0] == 'p')
				{
					int spacePos = 2;
					buff.clear();
					while (line[spacePos] != ' ')
					{
						buff.push_back(line[spacePos]);
						spacePos++;
					}
					positionsX[p] = atof(&buff[0]);
					buff.clear();
					for (int i = spacePos; i < line.size(); i++)
					{
						buff.push_back(line[i]);
					}
					positionsY[p] = atof(&buff[0]);
					//printf("\nPositions Loaded: %i /%f", p, timeTicks * count);
					if (p % 10000 == 0)
						printf("\nPositions Loaded: %i /%i", p, (int)round(timeTicks * count));
					p++;
				}
				else if (line[0] == 'v')
				{
					buff.clear();
					for (int i = 2; i < line.size(); i++)
					{
						buff.push_back(line[i]);
					}
					velocities[p-1] = atof(&buff[0]);
				}
			}

			loadFile.close();
			currentTime = 0;
		}
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
				donuts[i]->velocity = 3000000000000;
				angle = rand()* 1.f / RAND_MAX * two_pi<double>();
				donuts[i]->direction.x = cos(angle);
				donuts[i]->direction.y = sin(angle);
			}
			float secCount;
			printf("\nInput duration of simulation: ");
			std::cin >> secCount;

			deltaTime = donuts[0]->GetWidth()/10.f/donuts[0]->velocity;
			timeTicks = secCount * 60;
			positionsX = (float*)malloc(sizeof(float) * timeTicks * count);
			positionsY = (float*)malloc(sizeof(float) * timeTicks * count);
			velocities = (float*)malloc(sizeof(float) * timeTicks * count);
			simFile = std::ofstream("simulation.txt", std::ios_base::out);
			simFile << "c " << count << "\n";
			simFile << "t " << timeTicks << "\n";
			simFile << "s " << donuts[0]->GetWidth() << "\n";
			for (int i = 0; i < timeTicks; i++)
			{
				for (int j = 0; j < count; j++)
				{
					if((i*count+j)% 10000 == 0)
						printf("\nSimulated: %i /%i", i * count + j, (int)round(timeTicks * count));
					positionsX[i * count + j] = donuts[j]->position.x; 
					positionsY[i * count + j] = donuts[j]->position.y;
					velocities[i * count + j] = donuts[j]->velocity;
					simFile << "p " << donuts[j]->position.x << " " << donuts[j]->position.y << "\n";
					simFile << "d " << donuts[j]->direction.x << " " << donuts[j]->direction.y << "\n";
					simFile << "v " << donuts[j]->velocity << "\n";
					donuts[j]->Update(deltaTime);
				}
				Collider(&donuts[0]);
			}
			currentTime = 0;
			simFile.close();
			Screen::screenController->AddScreen(new MaxwellScreen(width, height));
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

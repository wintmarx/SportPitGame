#include "Game.h"
#include "Player.h"
#include "Burger.h"
#include "Cola.h"
#include "Food.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace glm;

mat4 projection;
mat4 view;
vec3 cameraPosition;
vec3 cameraZoom;

bool isStop = false;

Player *player;

std::vector<Food*> food;

const int cellsCount = 30;
int fieldSize;
int field[cellsCount][cellsCount];

std::string FPS;

Game::Game(int width, int height)
{
	screenHeight = height;
	screenWidth = width;
	//fieldSizeX = screenWidth / cellsCountX;
	fieldSize = (int)glm::round(screenHeight * 0.1f);//screenHeight / cellsCountY;

    glClearColor(.1f, .67f, 1.f, 1.f);

	projection = ortho(0.0f, width * 1.0f, 0.0f, height*1.0f, 1.0f, -1.0f);
	view = mat4(1);

	cameraPosition = vec3(0);
	cameraZoom = vec3(1);

	player = new Player(fieldSize, fieldSize, &vec3(fieldSize/2, fieldSize/2, 0));

	srand((uint32_t)time(0));

	for (int i = 0; i < cellsCount; i++)
	{
		for (int j = 0; j < cellsCount; j++)
		{
			field[i][j] = (int)rand()%7;
			if (field[i][j] == 1)
				food.push_back(new Burger(fieldSize, fieldSize, &glm::vec3(j * fieldSize + fieldSize/2, i * fieldSize + fieldSize/2, 0)));
			if (field[i][j] == 2)
				food.push_back(new Cola(fieldSize, fieldSize, &glm::vec3(j * fieldSize + fieldSize / 2, i * fieldSize + fieldSize / 2, 0)));
		}
	}
}

Game::~Game()
{
	
}

void Game::Update(float delta)
{
	isStop = player->IsOutField(cellsCount, cellsCount);
	if(!isStop)
		player->Update(delta);

	for (uint32_t i = 0; i < food.size(); i++)
	{
		if (player->position == food[i]->position)
		{
			food[i]->Eat(player);
			food.erase(food.begin() + i);
		}
	}

	view = translate(-player->position + vec3(screenWidth/2, screenHeight/2, 0));

	FPS = "FPS: " + std::to_string((int)round(1.f / delta));
}

void Game::Render(Graphics *graphics)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (int i = 0; i < cellsCount + 1; i++)
	{
		graphics->DrawLine(0, i * fieldSize, cellsCount * fieldSize, i * fieldSize, &glm::vec4(0, 0, 1, 1), &(projection*view));
	}
	for (int j = 0; j < cellsCount + 1; j++)
	{
		graphics->DrawLine(j * fieldSize, 0, j * fieldSize, cellsCount * fieldSize, &glm::vec4(0, 0, 1, 1), &(projection*view));
	}

	for (uint32_t i = 0; i < food.size(); i++)
	{
		food[i]->Draw(&projection, &view, graphics);
	}

	player->Draw(&projection, &view, graphics);

	graphics->arialFont->DrawText(&FPS[0], 72, &vec4(1, 1, 1, 1), 0, 100, &projection, graphics->spriteShader);

	//std::cout << glGetError() << std::endl;
}


void Game::OnKeyPress(int buttonID, bool isPressed)
{
	switch (buttonID)
	{
	case GLFW_KEY_SPACE:
		if (!isPressed)
			isStop = !isStop;
		break;
	case GLFW_KEY_W:
		if (!isPressed)
			view = glm::translate(view, glm::vec3(0, -fieldSize, 0));
		break;
	case GLFW_KEY_A:
		if (!isPressed)
			view = glm::translate(view, glm::vec3(fieldSize, 0, 0));
		break;
	case GLFW_KEY_S:
		if (!isPressed)
			view = glm::translate(view, glm::vec3(0, fieldSize, 0));
		break;
	case GLFW_KEY_D:
		if (!isPressed)
			view = glm::translate(view, glm::vec3(-fieldSize, 0, 0));
		break;
	case GLFW_KEY_2:
		//if (!isPressed)
		break;
	case GLFW_KEY_1:
		//if (!isPressed)
		break;
	case GLFW_KEY_G:
		//if (!isPressed)
		break;
	case GLFW_KEY_UP:
		player->direction.x = 0;
		player->direction.y = 1;
		break;
	case GLFW_KEY_DOWN:
		player->direction.x = 0;
		player->direction.y = -1;
		break;
	case GLFW_KEY_RIGHT:
		player->direction.x = 1;
		player->direction.y = 0;
		break;
	case GLFW_KEY_LEFT:
		player->direction.x = -1;
		player->direction.y = 0;
		break;
	case GLFW_KEY_EQUAL:
		if (!isPressed)
		{
			player->velocityLimiter += 0.002f;
			std::cout << std::endl << player->velocityLimiter;
		}
		break;
	case GLFW_KEY_MINUS:
		if (!isPressed)
		{
			if (player->velocityLimiter > 1.f / 60)
				player->velocityLimiter -= 0.002f;
			std::cout << std::endl << player->velocityLimiter;
		}
		break;
	}
}

void  Game::OnKeyRelease(int buttonID)
{
	switch (buttonID)
	{
	case GLFW_KEY_W:

		break;
	case GLFW_KEY_A:

		break;
	case GLFW_KEY_S:

		break;
	case GLFW_KEY_D:

		break;
	case GLFW_KEY_G:
		break;
	case GLFW_KEY_UP:
		break;
	case GLFW_KEY_DOWN:
		break;
	case GLFW_KEY_RIGHT:
		break;
	case GLFW_KEY_LEFT:
		break;
	case GLFW_KEY_EQUAL:
		break;
	case GLFW_KEY_MINUS:
		break;
	}
}

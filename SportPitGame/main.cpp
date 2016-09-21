#include <iostream>
#include <vector>
#include "..\GameEngine\Game.h"

#define WIDTH 840
#define HEIGHT 480
#define APP_NAME "Galaxy Savior"

void OnKeyboardEvent(GLFWwindow* window);
bool InitializeWindow(int width, int height);

GLFWwindow *window;
Game *game;
Graphics *graphics;
void main()
{
	if (!InitializeWindow(WIDTH, HEIGHT))
		return;
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	game = new Game(WIDTH, HEIGHT);
	graphics = new Graphics();
	graphics->screenWidth = WIDTH;
	graphics->screenHeight = HEIGHT;

	float lastTime = 0;
	float delta = 0;
	do
	{
		lastTime = (float)glfwGetTime();
		OnKeyboardEvent(window);
		game->Update(delta);
		game->Render(graphics);
		glfwSwapBuffers(window);
		glfwPollEvents();
		while (glfwGetTime() - lastTime < 1.f / 60) {}
		delta = (float)glfwGetTime() - lastTime;
	} while (glfwWindowShouldClose(window) == 0);

	delete game;
	delete graphics;

	glfwTerminate();
}

bool InitializeWindow(int width, int height)
{
	// Инициализируем GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW init error\n");
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, APP_NAME, NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Window create error");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "GLEW init error");
		return false;
	}
	return true;
}

bool isKeyPressed;
std::vector<int> pressedKeysId;

void OnKeyboardEvent(GLFWwindow* window)
{
	for (unsigned int i = GLFW_KEY_SPACE; i < GLFW_KEY_MENU; i++)
	{
		if (glfwGetKey(window, i) == GLFW_PRESS)
		{
			isKeyPressed = false;
			for (unsigned int j = 0; j < pressedKeysId.size(); j++)
			{
				if (i == pressedKeysId[j])
				{
					isKeyPressed = true;
				}
			}
			if (!isKeyPressed)
			{
				pressedKeysId.push_back(i);
			}
			game->OnKeyPress(i, isKeyPressed);
		}
	}
	for (unsigned int i = 0; i < pressedKeysId.size(); i++)
	{
		if (glfwGetKey(window, pressedKeysId[i]) == GLFW_RELEASE)
		{
			game->OnKeyRelease(pressedKeysId[i]);
			pressedKeysId.erase(pressedKeysId.begin() + i);
		}
	}
}

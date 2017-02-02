#include "GameScreen.h"


using namespace glm;

GameScreen::GameScreen(int width, int height) : Screen(width, height)
{
	//fieldSizeX = screenWidth / cellsCountX;
	fieldSize = (int)glm::round(width * 0.07f);//screenHeight / cellsCountY;

	glClearColor(.1f, .67f, 1.f, 1.f);

	projection = ortho(0.0f, width * 1.0f, 0.0f, height*1.0f, 1.0f, -1.0f);
	view = mat4(1);

	cameraPosition = vec3(0);
	cameraZoom = vec3(1);
}


GameScreen::~GameScreen()
{
	for (uint32_t i = 0; i < food.size(); i++)
	{
		delete food.back();
		food.pop_back();
	}
	delete player;
}

void GameScreen::Initialize()
{
	player = new Player(fieldSize, fieldSize, &vec3(fieldSize / 2, fieldSize / 2, 0));

	srand((uint32_t)time(0));

	//LoadLayout("..//..//Data//Layouts//text.layout");

	int step = 0;
	int randomNumber = 0;
	for (int i = 0; i < cellsCount; i++)
	{
		for (int j = 0; j < cellsCount; j++)
		{
			randomNumber = (int)(rand() % 8) + 1;
			step = int(rand() % (10 * fieldSize) + fieldSize / 2);
			if (randomNumber == 1)
				food.push_back(new Burger(fieldSize, fieldSize, &glm::vec3(j * step, i * step, 0)));
			if (randomNumber == 2)
				food.push_back(new Cola(fieldSize, fieldSize, &glm::vec3(j * step, i * step, 0)));
			if (randomNumber == 3)
				food.push_back(new Croissant(fieldSize, fieldSize, &glm::vec3(j * step, i * step, 0)));
			if (randomNumber == 4)
				food.push_back(new Donut(fieldSize, fieldSize, &glm::vec3(j * step, i * step, 0)));
			if (randomNumber == 5)
				food.push_back(new Banana(fieldSize, fieldSize, &glm::vec3(j * step, i * step, 0)));
		}
	}
}

void GameScreen::Update(float delta)
{
	//isStop = player->IsOutField(cellsCount, cellsCount);
	//if(!isStop)
	player->Update(delta);

	for (uint32_t i = 0; i < food.size(); i++)
	{
		if (length(player->position - food[i]->position) < fieldSize*3.f / 4)
		{
			food[i]->Eat(player);
			delete food[i];
			food.erase(food.begin() + i);
		}
	}

	view = translate(-player->position + vec3(width / 2, height / 2, 0));

	//FPS = "FPS: " + std::to_string((int)round(1.f / delta));
}

void GameScreen::Render(Graphics *graphics)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*for (int i = 0; i < cellsCount + 1; i++)
	{
	graphics->DrawLine(0, i * fieldSize, cellsCount * fieldSize, i * fieldSize, &glm::vec4(0, 0, 1, 1), &(projection*view));
	}
	for (int j = 0; j < cellsCount + 1; j++)
	{
	graphics->DrawLine(j * fieldSize, 0, j * fieldSize, cellsCount * fieldSize, &glm::vec4(0, 0, 1, 1), &(projection*view));
	}*/

	for (uint32_t i = 0; i < food.size(); i++)
	{
		food[i]->Draw(&projection, &view, graphics);
	}

	player->Draw(&projection, &view, graphics);

	//graphics->arialFont->DrawText(&FPS[0], 72, &vec4(1, 1, 1, 1), 0, 100, &projection, graphics->spriteShader, false);

	//for (uint32_t i = 0; i < graphics->textBlocks.size(); i++)
	//{
	//	graphics->DrawText(graphics->textBlocks[i], &projection, graphics->spriteShader, false);
	//}

	//std::cout << glGetError() << std::endl;
}

void GameScreen::LoadLayout(const char *filePath)
{
	uint8_t  *buffer;
	uint32_t size;
	uint32_t offset = 3;

	if (!FilesIOLibrary::LoadFile(filePath, &buffer, &size))
	{
		std::cout << "\nLoading layout error";
		delete[] buffer;
		return;
	}

	uint32_t textBlocksCount;
	FilesIOLibrary::ReadBinaryValue(&buffer, &textBlocksCount, &offset);

	for (uint32_t i = 0; i < textBlocksCount; i++)
	{
		float x;
		FilesIOLibrary::ReadBinaryValue(&buffer, &x, &offset);
		x *= width;

		float y;
		FilesIOLibrary::ReadBinaryValue(&buffer, &y, &offset);
		y *= height;

		float fontSize;
		FilesIOLibrary::ReadBinaryValue(&buffer, &fontSize, &offset);
		fontSize *= height;

		vec4 color;
		for (int i = 0; i < color.length(); i++)
		{
			FilesIOLibrary::ReadBinaryValue(&buffer, &color[i], &offset);
		}

		uint32_t textLength;
		FilesIOLibrary::ReadBinaryValue(&buffer, &textLength, &offset);

		std::string text = "";
		for (uint32_t j = 0; j < textLength; j++)
		{
			char glyph;
			FilesIOLibrary::ReadBinaryValue(&buffer, &glyph, &offset);
			text.push_back(glyph);
			std::cout << std::endl << +text[j];
		}
		//graphics->textBlocks.push_back(new TextBlock(&text, (int)fontSize, &color, x, y, graphics->calibriFont));
	}

	delete[] buffer;
}

void GameScreen::OnKeyPress(int buttonID, bool isPressed)
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
		player->velocity += 10.f;
		break;
	case GLFW_KEY_MINUS:
		player->velocity -= 10.f;
		break;
	case GLFW_KEY_BACKSPACE:
		screenController->PreviousScreen();
		break;
	}
}

void  GameScreen::OnKeyRelease(int buttonID)
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

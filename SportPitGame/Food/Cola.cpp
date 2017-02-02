#include "Cola.h"



Cola::Cola(int width, int height, glm::vec3 *position)
	: Food("..//..//Data//Textures//Food//lq//cola.png", width, height, position)
{
	calories = 210;
	fats = 0;
	carbohydrates = 55;
	proteins = 0;
}

Cola::~Cola()
{
}

void Cola::Update(float deltaTime)
{

}

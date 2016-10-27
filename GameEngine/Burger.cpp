#include "Burger.h"



Burger::Burger(int width, int height, glm::vec3 *position)
	: Food("..//..//Data//Textures//Food//lq//burger.png", width, height, position)
{
	calories = 509;
	fats = 29;
	carbohydrates = 42;
	proteins = 27;
}

Burger::~Burger()
{
}

void Burger::Update(float deltaTime)
{

}

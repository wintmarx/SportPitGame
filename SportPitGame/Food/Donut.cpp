#include "Donut.h"



Donut::Donut(int width, int height, glm::vec3 *position)
	: Food("..//..//Data//Textures//Food//lq//donutnew.png", width, height, position)
{
	calories = 210;
	fats = 0;
	carbohydrates = 55;
	proteins = 0;
}

Donut::~Donut()
{
}

void Donut::Update(float deltaTime)
{

}

#include "Croissant.h"



Croissant::Croissant(int width, int height, glm::vec3 *position)
	: Food("Food//lq//croissantnew.png", width, height, position)
{
	calories = 210;
	fats = 0;
	carbohydrates = 55;
	proteins = 0;
}

Croissant::~Croissant()
{
}

void Croissant::Update(float deltaTime)
{

}


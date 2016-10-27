#include "Banana.h"



Banana::Banana(int width, int height, glm::vec3 *position)
	: Food("..//..//Data//Textures//Food//lq//banana.png", width, height, position)
{
	calories = 509;
	fats = 29;
	carbohydrates = 42;
	proteins = 27;
}

Banana::~Banana()
{
}

void Banana::Update(float deltaTime)
{

}

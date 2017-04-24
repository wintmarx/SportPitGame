#include "Food.h"



Food::Food(const char *filePath, int width, int height, glm::vec3 *position)
	: Unit(width, height, filePath, position)
{
}


Food::~Food()
{

}

void Food::Eat(Player *player)
{
	player->EatFood(calories, carbohydrates, proteins, fats);
}

void Food::Update(float deltaTime)
{
	glm::vec3 deltaPos = direction * velocity * deltaTime;
	position += deltaPos;
	*model = glm::translate(position);
}
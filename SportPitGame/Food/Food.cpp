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

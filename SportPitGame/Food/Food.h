#pragma once
#include "../Player.h"

class Food :
	public Unit
{
public:
	Food(const char *filePath, int width, int height, glm::vec3 *position);
	~Food();
	virtual void Update(float deltaTime);
	void Eat(Player *player);
protected:
	int calories;
	int carbohydrates;
	int proteins;
	int fats;
};


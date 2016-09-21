#pragma once
#include "Unit.h"
#include <vector>

class Player : public Unit
{
public:
	Player(int width, int height, glm::vec3 *position);
	~Player();
	void Update(float deltaTime);
	void EatFood(int calories, int carbohydrates, int proteins, int fats);
	void Draw(glm::mat4 *projection, glm::mat4 *view, Graphics *graphics);
private:
	int calories;
	int carbohydrates;
	int proteins;
	int fats;
};


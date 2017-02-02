#pragma once
#include "Food.h"

class Burger :
	public Food
{
public:
	Burger(int width, int height, glm::vec3 *position);
	~Burger();
	void Update(float deltaTime);
};


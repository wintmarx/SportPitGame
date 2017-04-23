#pragma once
#include "Food.h"

class Banana :
	public Food
{
public:
	Banana(int width, int height, glm::vec3 *position);
	~Banana();
	void Update(float deltaTime);
};


#pragma once
#include "Food.h"

class Croissant :
	public Food
{
public:
	Croissant(int width, int height, glm::vec3 *position);
	~Croissant();
	void Update(float deltaTime);
};


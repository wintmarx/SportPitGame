#pragma once
#include "Food.h"

class Donut :
	public Food
{
public:
	Donut(int width, int height, glm::vec3 *position);
	~Donut();
	void Update(float deltaTime);
};


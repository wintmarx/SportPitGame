#pragma once
#include "Food.h"

class Cola :
	public Food
{
public:
	Cola(int width, int height, glm::vec3 *position);
	~Cola();
	void Update(float deltaTime);
	int x = 6;
};


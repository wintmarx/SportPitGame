#include "Unit.h"
#include <iostream>



Unit::Unit(int width, int height, glm::vec4 *color, glm::vec3 *position)
{
	sprite = new Sprite(width, height, color);
	InitializeUnit(position);
}

Unit::Unit(int width, int height, const char *filePath, glm::vec3 *position)
{
	sprite = new Sprite(width, height, filePath);
	InitializeUnit(position);
}

Unit::Unit(const char *filePath, glm::vec3 *position)
{
	sprite = new Sprite(filePath);
	InitializeUnit(position);
}

bool Unit::IsOutField(const int cellsCountX, const int cellsCountY)
{
	if (position.x / sprite->width + direction.x > cellsCountX || position.x / sprite->width + direction.x < 0)
		return true;
	if (position.y / sprite->height + direction.y > cellsCountY || position.y / sprite->height + direction.y < 0)
		return true;

	return false;
}

Unit::~Unit()
{
	delete model;
	delete sprite;
}

void Unit::InitializeUnit(glm::vec3 *position)
{
	this->position = *position;
	velocityTimer = 1;
	velocity = 0.5f;
	direction = glm::vec3(0);
	model = new glm::mat4(1);
	*model = glm::translate(*model, *position);
	*model = glm::scale(*model, glm::vec3(-1, 1, 1));
}

void Unit::Draw(glm::mat4 *projection, glm::mat4 *view, Graphics *graphics)
{
	if(position.x + (*view)[3].x > -sprite->width/2 && position.x + (*view)[3].x < graphics->screenWidth + sprite->width/2 && position.y + (*view)[3].y > -sprite->height/2 && position.y + (*view)[3].y < graphics->screenHeight + sprite->height/2)
		sprite->Draw(model, projection, view, graphics->spriteShader);
}

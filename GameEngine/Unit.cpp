#include "Unit.h"
#include <iostream>



Unit::Unit(int width, int height, glm::vec4 *color, glm::vec3 *position)
{
	sprite = new CommonSprite(position->x, position->y);
	sprite->SetColor(color);
	sprite->SetSize(width, height);
	sprite->SetShader("CommonSprite.vs", "CommonSprite.fs");
	InitializeUnit(position);
}

Unit::Unit(int width, int height, const char *filePath, glm::vec3 *position)
{
	sprite = new CommonSprite(position->x, position->y);
	sprite->SetTexture(filePath, true);
	sprite->SetSize(width, height);
	sprite->SetShader("CommonSprite.vs", "CommonSprite.fs");
	InitializeUnit(position);
}

Unit::Unit(const char *filePath, glm::vec3 *position)
{
	sprite = new CommonSprite(position->x, position->y);
	sprite->SetTexture(filePath, true);
	sprite->SetShader("CommonSprite.vs", "CommonSprite.fs");
	InitializeUnit(position);
}

Unit::~Unit()
{
	delete sprite;
}

int Unit::GetWidth()
{
	return sprite->width;
}

int Unit::GetHeight()
{
	return sprite->height;
}

void Unit::InitializeUnit(glm::vec3 *position)
{
	this->position = *position;
	velocityTimer = 1;
	velocity = 0.5f;
	direction = glm::vec3(0);
}

void Unit::Draw(glm::mat4 *projection, glm::mat4 *view, Graphics *graphics)
{
	if (position.x + (*view)[3].x > -sprite->width / 2 && position.x + (*view)[3].x < graphics->screenWidth + sprite->width / 2 && position.y + (*view)[3].y > -sprite->height / 2 && position.y + (*view)[3].y < graphics->screenHeight + sprite->height / 2)
	{
		sprite->SetPosition(position.x, position.y);
		sprite->Draw(projection, view);
	}
}

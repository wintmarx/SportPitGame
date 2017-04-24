#include "Player.h"
#include <iostream>
#include <string>



Player::Player(int width, int height, glm::vec3 *position) 
	: Unit(width, height, "player.png", position)
{
	direction.x = 1;
	this->calories = 2800;
	this->carbohydrates = 320;
	this->proteins = 160;
	this->fats = 50;
	velocity = 500;
	sprite->SetColor(&glm::vec4(0, 0, 0, 1));
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
	position.x += direction.x * velocity * deltaTime;
	position.y += direction.y * velocity * deltaTime;
	this->calories -= 116;
	this->carbohydrates -= 12;
	this->proteins -= 7;
	this->fats -= 2;
	*model = glm::translate(position);
}

void Player::EatFood(int calories, int carbohydrates, int proteins, int fats)
{
	this->calories += calories;
	this->carbohydrates += carbohydrates;
	this->proteins += proteins;
	this->fats += fats;
}

void Player::Draw(glm::mat4 *projection, glm::mat4 *view, Graphics *graphics)
{
	std::string infoString = "";
	infoString += "calories: " + std::to_string(this->calories);
	infoString += "\nfats: " + std::to_string(this->fats);
	infoString += "\ncarbohydrates: " + std::to_string(this->carbohydrates);
	infoString += "\nproteins: " + std::to_string(this->proteins);
	//graphics->arialFont->DrawText(&infoString[0], 30, &glm::vec4(0.81, 0, 0, 1), 0, graphics->screenHeight, projection, graphics->spriteShader);
	//graphics->arialBFont->DrawText(&infoString[0], 30, &glm::vec4(1, 1, 0, 1), 0, graphics->screenHeight, projection, graphics->spriteShader);
	Unit::Draw(projection, view, graphics);
}


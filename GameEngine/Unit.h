#pragma once
#include "..\\Graphics\Graphics.h"
#include "..\\Graphics\Sprite.h"



class Unit
{
public:
	virtual void Draw(glm::mat4 *projection, glm::mat4 *view, Graphics *graphics);
	virtual void Update(float deltaTime) = 0;
	Unit(int width, int height, glm::vec4 *color, glm::vec3 *position);
	Unit(int width, int height, const char* filePath, glm::vec3 *position);
	Unit(const char* filePath, glm::vec3 *position);
	bool IsOutField(const int cellsCountX, const int cellsCountY);
	~Unit();
	glm::vec3 position;
	glm::vec3 direction;
	float velocityTimer;
	float velocity;
protected:
	void InitializeUnit(glm::vec3 *position);
	Sprite *sprite;
	glm::mat4 *model;
private:
	SpriteShader *spriteShader;
};


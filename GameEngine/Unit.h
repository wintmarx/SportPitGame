#pragma once
#include "..\Graphics\Graphics.h"
#include "..\Graphics\CommonSprite.h"
#ifdef GAMEENGINE_EXPORTS
#define GAMEENGINE_API __declspec(dllexport) 
#else
#define GAMEENGINE_API __declspec(dllimport)
#endif



class Unit
{
public:
	GAMEENGINE_API virtual void Draw(glm::mat4 *projection, glm::mat4 *view, Graphics *graphics);
	GAMEENGINE_API virtual void Update(float deltaTime) = 0;
	GAMEENGINE_API Unit(int width, int height, glm::vec4 *color, glm::vec3 *position);
	GAMEENGINE_API Unit(int width, int height, const char* filePath, glm::vec3 *position);
	GAMEENGINE_API Unit(const char* filePath, glm::vec3 *position);
	GAMEENGINE_API int GetWidth();
	GAMEENGINE_API int GetHeight();
		
	GAMEENGINE_API ~Unit();
	glm::vec3 position;
	glm::vec3 direction;
	float velocityTimer;
	float velocity;
protected:
	void InitializeUnit(glm::vec3 *position);
	CommonSprite *sprite;
};


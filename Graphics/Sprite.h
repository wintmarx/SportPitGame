#pragma once
#include "GLHeaders.h"
#include "SpriteShader.h"
#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport) 
#else
#define GRAPHICS_API __declspec(dllimport)
#endif



class Sprite
{

public:
	GRAPHICS_API Sprite(int width, int height, glm::vec4 *color);
	GRAPHICS_API Sprite(const char* filePath);
	GRAPHICS_API Sprite(const char* filePath, glm::vec4 *color);
	GRAPHICS_API Sprite(int width, int height, const char* filePath);
	GRAPHICS_API ~Sprite();
	GRAPHICS_API void Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view, SpriteShader *spriteShader);
	GRAPHICS_API void SetShape(float x, float y, int width, int height);
	GRAPHICS_API void SetColor(glm::vec4 *color);
	int width;
	int height;
	
private:
	void InitializeSprite();
	static const int vertexCount = 4;
	static const int indexCount = 6;
	glm::vec4 color;

	GLuint vertexBuffer;
	GLuint textureBuffer;
	GLuint indexBuffer;
	GLuint textureId;
};


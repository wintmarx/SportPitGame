#pragma once
#include "GLHeaders.h"
#include "SpriteShader.h"



class Sprite
{

public:
	__declspec(dllexport) Sprite(int width, int height, glm::vec4 *color);
	__declspec(dllexport) Sprite(const char* filePath);
	__declspec(dllexport) Sprite(const char* filePath, glm::vec4 *color);
	__declspec(dllexport) Sprite(int width, int height, const char* filePath);
	__declspec(dllexport) ~Sprite();
	__declspec(dllexport) void Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view, SpriteShader *spriteShader);
	__declspec(dllexport) void SetShape(float x, float y, int width, int height);
	__declspec(dllexport) void SetColor(glm::vec4 *color);
	int width;
	int height;
	
private:
	void LoadTexture(const char* filePath);
	void InitializeSprite();
	static const int vertexCount = 4;
	static const int indexCount = 6;
	glm::vec4 color;

	GLuint vertexBuffer;
	GLuint textureBuffer;
	GLuint indexBuffer;
	GLuint textureId;
};


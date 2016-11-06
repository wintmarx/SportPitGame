#pragma once
#include "GLHeaders.h"
#include "SpriteShader.h"
#include "TexturesController.h"
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
	static void SetTexturesController(TexturesController *texturesController);
	int width;
	int height;
private:
	void InitializeSprite();
	static const int vertexCount;
	static const int indexCount;
	glm::vec4 color;
	uint32_t textureId;
	static TexturesController *texturesController;
	GLuint vertexBuffer;
	GLuint textureBuffer;
	GLuint indexBuffer;
};


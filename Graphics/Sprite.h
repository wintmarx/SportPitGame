#pragma once
#include "GLHeaders.h"
#include "TexturesController.h"
#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport) 
#else
#define GRAPHICS_API __declspec(dllimport)
#endif



class Sprite
{

public:
	GRAPHICS_API Sprite(char *filePath, int width, int height);
	GRAPHICS_API ~Sprite();
	GRAPHICS_API virtual void Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view) = 0;
	GRAPHICS_API void SetShape(float x, float y, int width, int height);
	GRAPHICS_API void SetColor(glm::vec4 *color);
	GRAPHICS_API void Set(glm::vec4 *color);
	static void SetTexturesController(TexturesController *texturesController);
	int width;
	int height;
protected:
	void InitializeSprite();
	static const int vertexCount;
	static const int indexCount;
	glm::vec4 color;
	static TexturesController *texturesController;
	GLuint textureId;
	GLuint vertexBuffer;
	GLuint textureBuffer;
	GLuint indexBuffer;
	GLuint vertexArrayObject;
};


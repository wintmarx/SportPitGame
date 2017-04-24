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
	GRAPHICS_API Sprite();
	GRAPHICS_API ~Sprite();
	GRAPHICS_API virtual void Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view) = 0;
	GRAPHICS_API void SetSize(int width, int height);
	GRAPHICS_API void SetTextureShape(float uvX, float uvY, int width, int height);
	GRAPHICS_API void SetColor(glm::vec4 *color);
	GRAPHICS_API void SetTexture(const char* filePath);
	GRAPHICS_API virtual void SetShader(const char *vFilePath, const char *fFilePath) = 0;
	GRAPHICS_API void SetActiveShader(int localShaderId);
	static void SetTexturesController(TexturesController *texturesController);
	int width;
	int height;
protected:
	void InitializeSprite();
	static const int8_t vertexCount = 4;
	static const int8_t indexCount = 6;
	glm::vec4 color;
	static TexturesController *texturesController;
	GLuint textureId;
	int currentShader;
	GLuint vertexBuffer;
	GLuint textureBuffer;
	GLuint indexBuffer;
	GLuint vertexArrayObject;
};


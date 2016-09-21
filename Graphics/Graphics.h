#pragma once
#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport) 
#else
#define GRAPHICS_API __declspec(dllimport)
#endif

#include "GLHeaders.h"
#include "SpriteShader.h"
#include "TextureTGA.h"
#include "Line.h"
#include "TextFont.h"

class Graphics
{
public:
	SpriteShader *spriteShader;
	GRAPHICS_API Graphics();
	GRAPHICS_API ~Graphics();
	GRAPHICS_API GLuint LoadShaders(const char *vFilePath, const char *fFilePath);
	GRAPHICS_API void DrawLine(float x1, float y1, float x2, float y2, glm::vec4 *color, glm::mat4 *projection);
	TextFont *arialFont;
	TextFont *chillerFont;
	TextFont *arialBFont;
	int screenWidth;
	int screenHeight;
private:
	GLuint VertexArrayID;
	Line *line;
};




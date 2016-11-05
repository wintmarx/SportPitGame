#pragma once
#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport) 
#else
#define GRAPHICS_API __declspec(dllimport)
#endif

#include "GLHeaders.h"
#include "SpriteShader.h"
#include "TGALoader.h"
#include "Line.h"
#include "TextBlock.h"
#include "TexturesController.h"
#include <vector>

class Graphics
{
public:
	GRAPHICS_API Graphics();
	GRAPHICS_API ~Graphics();
	GRAPHICS_API void DrawText(TextBlock *textBlock, glm::mat4 *projection, SpriteShader *spriteShader, bool isRected);
	GRAPHICS_API void DrawLine(float x1, float y1, float x2, float y2, glm::vec4 *color, glm::mat4 *projection);
	SpriteShader *spriteShader;
	TextFont *arialFont;
	TextFont *chillerFont;
	TextFont *calibriFont;
	TextFont *sagoePrintFont;
	int screenWidth;
	int screenHeight;
	std::vector<TextBlock*> textBlocks;
private:
	GLuint vertexArrayId;
	TexturesController *texturesController;
	Line *line;
};




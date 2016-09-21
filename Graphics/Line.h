#pragma once
#include "GLHeaders.h"
#include "SpriteShader.h"



class Line
{

public:
	Line(float x1, float y1, float x2, float y2, glm::vec4 *color);
	~Line();
	void Draw(glm::mat4 *projection, SpriteShader *spriteShader);
	void SetLine(float x1, float y1, float x2, float y2, glm::vec4 *color);

private:
	static const int vertexCount = 2;
	glm::vec4 color;
	GLuint vertexBuffer;
};


#include "Line.h"
#include <iostream>


Line::Line()
{
	glGenBuffers(1, &vertexBuffer);
}

Line::Line(float x1, float y1, float x2, float y2, glm::vec4 *color)
{
	glGenBuffers(1, &vertexBuffer);
	SetLine(x1, y1, x2, y2, color);
}

Line::~Line()
{
	glDeleteBuffers(1, &vertexBuffer);
}

void Line::Draw(glm::mat4 *projection, SpriteShader *spriteShader)
{
	glUseProgram(spriteShader->programId);

	glUniformMatrix4fv(spriteShader->mvpShLoc, 1, GL_FALSE, &(*projection)[0][0]);
	glUniform4fv(spriteShader->matDiffColorShLoc, 1, &(color)[0]);
	glUniform1i(spriteShader->isColoredShLoc, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_LINES, 0, vertexCount * 2);

	glDisableVertexAttribArray(0);
}

void Line::SetLine(float x1, float y1, float x2, float y2, glm::vec4 * color)
{
	this->color = *color;

	float *vertices = (float*)malloc(sizeof(float) * vertexCount * 2);
	vertices[0] = x1;
	vertices[1] = y1;

	vertices[2] = x2;
	vertices[3] = y2;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, vertices, GL_STATIC_DRAW);
}

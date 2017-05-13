#include "Line.h"
#include <iostream>


Line::Line()
{
	glGenBuffers(1, &vertexBuffer);
	glGenVertexArrays(1, &vertexArrayObject);
	shader = new SpriteShader("CommonSprite.vs", "CommonSprite.fs");
}

Line::Line(float x1, float y1, float x2, float y2, glm::vec4 *color)
{
	glGenBuffers(1, &vertexBuffer);
	glGenVertexArrays(1, &vertexArrayObject);
	shader = new SpriteShader("CommonSprite.vs", "CommonSprite.fs");
	SetLine(x1, y1, x2, y2, color);
}

Line::~Line()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Line::Draw(glm::mat4 *projection)
{
	glUseProgram(shader->programId);
	glUniformMatrix4fv(shader->mvpShLoc, 1, GL_FALSE,  &(*projection)[0][0]);
	glUniform4fv(shader->matDiffColorShLoc, 1, &(color)[0]);
	glUniform1i(shader->isColoredShLoc, 0);

	glBindVertexArray(vertexArrayObject);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, vertexCount * 2);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Line::SetLine(float x1, float y1, float x2, float y2, glm::vec4 *color)
{
	this->color = *color;

	float *vertices = (float*)malloc(sizeof(float) * vertexCount * 2);
	vertices[0] = x1;
	vertices[1] = y1;

	vertices[2] = x2;
	vertices[3] = y2;

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glBufferSubData()
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete vertices;
}

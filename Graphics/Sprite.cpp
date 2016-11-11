#include "Sprite.h"
#include <iostream>
#include <vector>
#include "PNGLoader.h"
#include "TGALoader.h"

Sprite::Sprite(int width, int height, glm::vec4 *color)
{
	this->color = *color;
	this->textureId = 0;
	this->width = width;
	this->height = height;
	InitializeSprite();
}

Sprite::Sprite(const char *filePath)
{
	textureId = texturesController->AddTexture(filePath);
	height = texturesController->GetTextureHeight(textureId);
	width = texturesController->GetTextureWidth(textureId);
	color = glm::vec4(-1);
	InitializeSprite();
}

Sprite::Sprite(const char *filePath, glm::vec4 *color)
{
	this->color = *color;
	textureId = texturesController->AddTexture(filePath);
	height = texturesController->GetTextureHeight(textureId);
	width = texturesController->GetTextureWidth(textureId);
	InitializeSprite();
}

Sprite::Sprite(int width, int height, const char *filePath)
{
	this->width = width;
	this->height = height;
	textureId = texturesController->AddTexture(filePath);
	color = glm::vec4(-1);
	InitializeSprite();
}

Sprite::~Sprite()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &textureBuffer);
}

void Sprite::Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view, SpriteShader *spriteShader)
{
	glUseProgram(spriteShader->programId);

	if (textureId > 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glUniform1i(spriteShader->texSamplerShLoc, 0);
	}

	glUniformMatrix4fv(spriteShader->mvpShLoc, 1, GL_FALSE, &((*projection) * (*view) * (*model))[0][0]);
	glUniform4fv(spriteShader->matDiffColorShLoc, 1, &(color)[0]);

	if (textureId > 0 && color.x >= 0)
	{
		glUniform1i(spriteShader->isColoredShLoc, 1);
	}
	else
	{
		glUniform1i(spriteShader->isColoredShLoc, 0);
	}

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

const int Sprite::vertexCount = 4;
const int Sprite::indexCount = 6;
void Sprite::InitializeSprite()
{
	float *vertices = (float*)malloc(sizeof(float) * vertexCount * 2);
	vertices[0] = -width / 2;
	vertices[1] = -height / 2;

	vertices[2] = -width / 2;
	vertices[3] = height / 2;

	vertices[4] = width / 2;
	vertices[5] = height / 2;

	vertices[6] = width / 2;
	vertices[7] = -height / 2;

	float *uvs = (float*)malloc(sizeof(float) * vertexCount * 2);
	uvs[0] = 1;
	uvs[1] = 1;

	uvs[2] = 1;
	uvs[3] = 0;

	uvs[4] = 0;
	uvs[5] = 0;

	uvs[6] = 0;
	uvs[7] = 1;

	unsigned int *indices = (unsigned int*)malloc(sizeof(unsigned int) * indexCount);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, uvs, GL_STATIC_DRAW);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	delete vertices;
	delete indices;
	delete uvs;
}

void Sprite::SetShape(float x, float y, int width, int height)
{
	float *vertices = (float*)malloc(sizeof(float) * vertexCount * 2);
	vertices[0] = -width / 2;
	vertices[1] = -height / 2;

	vertices[2] = -width / 2;
	vertices[3] = height / 2;

	vertices[4] = width / 2;
	vertices[5] = height / 2;

	vertices[6] = width / 2;
	vertices[7] = -height / 2;

	float *uvs = (float*)malloc(sizeof(float) * vertexCount * 2);
	uvs[0] = x / this->width;
	uvs[1] = y / this->height;

	uvs[2] = x / this->width;
	uvs[3] = y / this->height + height * 1.f / this->height;

	uvs[4] = x / this->width + width * 1.f / this->width;
	uvs[5] = y / this->height + height * 1.f / this->height;

	uvs[6] = x / this->width + width *1.f / this->width;
	uvs[7] = y / this->height;

	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, uvs, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, vertices, GL_STATIC_DRAW);

	delete vertices;
	delete uvs;
}

void Sprite::SetColor(glm::vec4 *color)
{
	this->color = *color;
}

TexturesController *Sprite::texturesController;
void Sprite::SetTexturesController(TexturesController *_texturesController)
{
	texturesController = _texturesController;
}



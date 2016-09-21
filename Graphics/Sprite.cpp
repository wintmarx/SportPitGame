#include "Sprite.h"
#include <iostream>
#include <vector>
#include "PNGLoader.h"
#include "TextureTGA.h"

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
	LoadTexture(filePath);
	InitializeSprite();
}

Sprite::Sprite(const char *filePath, glm::vec4 *color)
{
	LoadTexture(filePath);
	this->color = *color;
	InitializeSprite();
}

Sprite::Sprite(int width, int height, const char * filePath)
{
	LoadTexture(filePath);
	this->width = width;
	this->height = height;
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
}

void Sprite::LoadTexture(const char* filePath)
{
	color = glm::vec4(-1);

	// Load file and decode image.
	std::vector<unsigned char> image;
	unsigned int width, height;
	unsigned int error = lodepng::decode(image, width, height, filePath);

	// If there's an error, display it.
	if (error != 0)
	{
		std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
		return;
	}

	// запросим у OpenGL свободный индекс текстуры
	glGenTextures(1, &textureId);

	// сделаем текстуру активной
	glBindTexture(GL_TEXTURE_2D, textureId);

	// установим параметры фильтрации текстуры - линейная фильтрация
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// установим параметры "оборачивания" текстуры - отсутствие оборачивания
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// загрузим данные о цвете в текущую автивную текстуру
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	this->width = width;
	this->height = height;
}

void Sprite::SetShape(float x, float y, int width, int height)
{
	float *vertices = (float*)malloc(sizeof(float) * vertexCount * 2);
	vertices[0] = -width / 2;
	vertices[1] = height / 2;

	vertices[2] = -width / 2;
	vertices[3] = -height / 2;

	vertices[4] = width / 2;
	vertices[5] = -height / 2;

	vertices[6] = width / 2;
	vertices[7] = height / 2;

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
}

void Sprite::SetColor(glm::vec4 *color)
{
	this->color = *color;
}



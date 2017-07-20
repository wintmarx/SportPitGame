#include "Sprite.h"
#include <iostream>
#include <vector>

Sprite::Sprite(float x, float y)
{
	color = glm::vec4(-1);
	textureId = 0;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	float *uvs = (float*)malloc(sizeof(float) * vertexCount * 2);
	uvs[0] = 1;
	uvs[1] = 1;

	uvs[2] = 1;
	uvs[3] = 0;

	uvs[4] = 0;
	uvs[5] = 0;

	uvs[6] = 0;
	uvs[7] = 1;
	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, uvs, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	delete uvs;

	unsigned int *indices = (unsigned int*)malloc(sizeof(unsigned int) * indexCount);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	model = glm::scale(glm::vec3(-1, 1, 1));
	SetPosition(x, y);

	delete indices;
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &textureBuffer);
}

//const int Sprite::vertexCount = 4;
//const int Sprite::indexCount = 6;
void Sprite::InitializeSprite()
{
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

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, uvs, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete indices;
	delete uvs;
}

void Sprite::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
	float *vertices = (float*)malloc(sizeof(float) * vertexCount * 2);
	vertices[0] = -width / 2;
	vertices[1] = -height / 2;

	vertices[2] = -width / 2;
	vertices[3] = height / 2;

	vertices[4] = width / 2;
	vertices[5] = height / 2;

	vertices[6] = width / 2;
	vertices[7] = -height / 2;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, vertices, GL_STATIC_DRAW);

	delete vertices;
}

void Sprite::SetTextureShape(float uvX, float uvY, int width, int height)
{
	SetSize(width, height);

	float *uvs = (float*)malloc(sizeof(float) * vertexCount * 2);
	uvs[0] = uvX / this->width;
	uvs[1] = uvY / this->height;

	uvs[2] = uvX / this->width;
	uvs[3] = uvY / this->height + height * 1.f / this->height;

	uvs[4] = uvX / this->width + width * 1.f / this->width;
	uvs[5] = uvY / this->height + height * 1.f / this->height;

	uvs[6] = uvX / this->width + width *1.f / this->width;
	uvs[7] = uvY / this->height;

	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, uvs, GL_STATIC_DRAW);

	delete uvs;
}

void Sprite::SetPosition(float x, float y)
{
	model[3].x = x;
	model[3].y = y;
}

void Sprite::SetPosition(glm::vec3 *position)
{
	model[3].x = position->x;
	model[3].y = position->y;
}

void Sprite::SetTexture(const char* filePath)
{
	textureId = texturesController->AddTexture(filePath);
	width = texturesController->GetTextureWidth(textureId);
	height = texturesController->GetTextureHeight(textureId);
	SetSize(width, height);
}

void Sprite::SetActiveShader(int localShaderId)
{
	if (localShaderId < 0)
	{
		std::cout << "Shader id < 0";
		return;
	}
	currentShader = localShaderId;
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



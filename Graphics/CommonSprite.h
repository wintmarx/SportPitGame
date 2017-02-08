#pragma once
#include "Sprite.h"
#include "Shader.h"

class CommonSprite :
	public Sprite
{
public:
	GRAPHICS_API CommonSprite(GLuint textureId, int width, int height);
	GRAPHICS_API void Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view);
	Shader *shader;
	GLint mvpShLoc;
	GLint texSamplerShLoc;
	GLint matDiffColorShLoc;
	GLint isColoredShLoc;
};


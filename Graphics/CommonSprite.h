#pragma once
#include "Sprite.h"
#include "Shader.h"

class CommonSprite :
	public Sprite
{
public:
	GRAPHICS_API CommonSprite(GLuint textureId);
	GRAPHICS_API void Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view);
private:
	Shader *shader;
	GLint mvpShLoc;
	GLint texSamplerShLoc;
	GLint matDiffColorShLoc;
	GLint isColoredShLoc;
};


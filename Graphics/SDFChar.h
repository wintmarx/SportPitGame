#pragma once
#include "Sprite.h"
class SDFChar :
	public Sprite
{
public:
	GRAPHICS_API SDFChar(GLuint textureId, int width, int height);
	GRAPHICS_API void Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view);
};


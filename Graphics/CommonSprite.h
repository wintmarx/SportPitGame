#pragma once
#include "Sprite.h"
#include "SpriteShader.h"

class CommonSprite :
	public Sprite
{
public:
	GRAPHICS_API CommonSprite();
	GRAPHICS_API void Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view);
	GRAPHICS_API void SetShader(const char *vFilePath, const char *fFilePath);

private:
	static std::vector<SpriteShader*> shaders;
};

